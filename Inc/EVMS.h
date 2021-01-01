#include "main.h"
#include "utility_funcs.h"

#ifndef EVMS_H
#define EVMS_H

#define VAL_BRAKE_ANGLE_RTD 3500 
#define PWM_MAX_OUTPUT       199
typedef enum 
{
IDLE, 
PRECHARGE, 
NEUTRAL, 
DRIVE, 
DISCHARGE
}Modes_enum;

typedef enum 
{
NOERROR, 
FATAL
}Error_enum;



//DECLERATIONS//
void EVMS_Init();
void loop();
void IDLE_Func();
void PRECHARGE_Func();
void NEUTRAL_Func();
void DISCHARGE_Func();


void ErrorAction();

uint16_t uint16_t_Read_APPS();




#endif