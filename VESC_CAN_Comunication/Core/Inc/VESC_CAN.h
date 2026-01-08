#ifndef INC_VESC_CAN_H_
#define INC_VESC_CAN_H_

#include "main.h"
#include "stdint.h"

/**while setting in ioc file, set prescaler, tim_segment_1 and tim_segment_2 according to CAN_Baud_rate
CAN_Baud_rate should be same from both sides.
**/

class VESC{
public:
CAN_HandleTypeDef* vesc_hcan;
CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;

uint8_t controller_id;
uint32_t TxMailbox;

struct StatusData1 {
    float rpm;
    float current;
    float duty;
};
StatusData1 status1;

float sendCommand(uint8_t command, uint8_t* data);

// Constructor
VESC(CAN_HandleTypeDef* hcan, uint8_t controller_id);

// Control methods
float setRPM(int32_t rpm);
float setPosition(int32_t pos);
float setCurrent(int32_t current);
float setBrakeCurrent(int32_t brake_current);
float setHandBrakeCurrent(int32_t handBrake_current);
float setDuty(float duty);

// Status methods
bool processRxMessage(CAN_RxHeaderTypeDef* pHeader, uint8_t* pData);
StatusData1 getStatus1();

// Command definitions
static const uint8_t CMD_SET_DUTY = 0;
static const uint8_t CMD_SET_CURRENT = 1;
static const uint8_t CMD_SET_CURRENT_BRAKE = 2;
static const uint8_t CMD_SET_RPM = 3;
static const uint8_t CMD_SET_POS = 4;
static const uint8_t STATUS_1 = 9;
static const uint8_t CMD_SET_CURRENT_HANDBRAKE = 12;
};

#endif /* INC_VESC_CAN_H_ */
