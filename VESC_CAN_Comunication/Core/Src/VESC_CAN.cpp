#include "VESC_CAN.h"

VESC::VESC(CAN_HandleTypeDef* hcan, uint8_t id) {
vesc_hcan = hcan;
controller_id = id;
//in vesc, it uses extended id
// Extended ID format:
// | 29-bit identifier |
// | bits 0-7 | bits 8-15 | bits 16-28 |
// | VESC ID | Command | Reserved |
// Initialize CAN header settings
TxHeader.IDE = CAN_ID_EXT;
TxHeader.RTR = CAN_RTR_DATA;
TxHeader.DLC = 4;

// Initialize status data
status1 = {0};
}

float VESC::sendCommand(uint8_t command, uint8_t* data) {
TxHeader.ExtId = (command << 8) | controller_id;
return HAL_CAN_AddTxMessage(vesc_hcan, &TxHeader, data, &TxMailbox);
}

float VESC::setRPM(int32_t rpm) {
uint8_t data[4];

// Pack RPM value in big-endian format
data[0] = (rpm >> 24) & 0xFF;
data[1] = (rpm >> 16) & 0xFF;
data[2] = (rpm >> 8) & 0xFF;
data[3] = rpm & 0xFF;

return sendCommand(CMD_SET_RPM, data);
}

float VESC::setPosition(int32_t pos) {
uint8_t data[4];

// Pack position value in big-endian format
data[0] = (pos >> 24) & 0xFF;
data[1] = (pos >> 16) & 0xFF;
data[2] = (pos >> 8) & 0xFF;
data[3] = pos & 0xFF;

return sendCommand(CMD_SET_POS, data);
}

float VESC::setCurrent(int32_t current) {
uint8_t data[4];

current *= 1000; //converted current mA into A

// Pack current value in big-endian format (in milliamps)
data[0] = (current >> 24) & 0xFF;
data[1] = (current >> 16) & 0xFF;
data[2] = (current >> 8) & 0xFF;
data[3] = current & 0xFF;

return sendCommand(CMD_SET_CURRENT, data);
}

float VESC::setBrakeCurrent(int32_t brake_current) {
uint8_t data[4];

brake_current *= 1000;
// Pack brake current value in big-endian format (in milliamps)
data[0] = (brake_current >> 24) & 0xFF;
data[1] = (brake_current >> 16) & 0xFF;
data[2] = (brake_current >> 8) & 0xFF;
data[3] = brake_current & 0xFF;

return sendCommand(CMD_SET_CURRENT_BRAKE, data);
}

float VESC::setHandBrakeCurrent(int32_t current) {
uint8_t data[4];

current *= 1000;

// Pack current value in big-endian format (in milliamps)
data[0] = (current >> 24) & 0xFF;
data[1] = (current >> 16) & 0xFF;
data[2] = (current >> 8) & 0xFF;
data[3] = current & 0xFF;

return sendCommand(CMD_SET_CURRENT_HANDBRAKE, data);
}

float VESC::setDuty(float duty) {
uint8_t data[4];
int32_t duty_i;

duty_i = (int32_t)(duty * 100000.0f);

// Pack duty cycle value in big-endian format
data[0] = (duty_i >> 24) & 0xFF;
data[1] = (duty_i >> 16) & 0xFF;
data[2] = (duty_i >> 8) & 0xFF;
data[3] = duty_i & 0xFF;

return sendCommand(CMD_SET_DUTY, data);
}

bool VESC::processRxMessage(CAN_RxHeaderTypeDef* pHeader, uint8_t* pData) {
    if (pHeader->IDE != CAN_ID_EXT) {
    }
    uint8_t id = pHeader->ExtId & 0xFF;
    uint8_t cmd = (pHeader->ExtId >> 8) & 0xFF;

    if (id != controller_id) {
        return false;
    }

    if (cmd == STATUS_1 && pHeader->DLC >= 8) {
        int32_t erpm = (pData[0] << 24) | (pData[1] << 16) | (pData[2] << 8) | pData[3];
        int16_t current = (pData[4] << 8) | pData[5];
        int16_t duty = (pData[6] << 8) | pData[7];

        status1.rpm = (float)erpm;
        status1.current = (float)current / 10.0f; // Current in Amps
        status1.duty = (float)duty / 1000.0f; // Duty cycle as a fraction

        return true;
    }

    return false;
}

VESC::StatusData1 VESC::getStatus1() {
    return status1;
}
