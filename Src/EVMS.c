#include "EVMS.h"

extern Modes_enum currStateM = IDLE;
extern Modes_enum nextStateM = IDLE;

Error_enum currStateE = NOERROR;
Error_enum nextStateE = NOERROR;
uint16_t val[3];
// val[0] -> apps1, val[1]->apps2 , val[2]->brakes angle sensor


uint16_t uint16_t_Read_APPS()
{
	//this function reads the apps several time and gets it average to eleminate error in the reading
	//for now we only read one apps and dont check for plauability
	uint16_t apps1_read=0;
	for(int i=0;i<10;i++)
	{
		apps1_read+=val[0];
	}

	return (apps1_read/10);

}


void EVMS_Init()
{

    
   HAL_ADC_Start_DMA(&hadc1,val,3);
	
   HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
}


void IDLE_Func()
{

	HAL_GPIO_WritePin(EVMS_RELAY_GPIO_Port,EVMS_RELAY_Pin,1);
	//if the start button is not pressed then the next state is still idle state
	// this if can be removed and dont think the code functionality will be changed3
	if(! HAL_GPIO_ReadPin(START_BTN_GPIO_Port,START_BTN_Pin))
	{
		nextStateM=IDLE;
	}
    //else if the start button is pressed then the next state is 
	else if(HAL_GPIO_ReadPin(START_BTN_GPIO_Port,START_BTN_Pin))
	{
		// wait until the driver releases his hand from the start button
		while(HAL_GPIO_ReadPin(START_BTN_GPIO_Port,START_BTN_Pin));
		HAL_Delay(50); //wait for button debouncing 
		nextStateM=PRECHARGE;
	}
	currStateM=nextStateM;

}

void PRECHARGE_Func()
{

	// close the precharge relaay of bamocar
	HAL_GPIO_WritePin(PRECHARGE_RELAY_GPIO_Port,PRECHARGE_RELAY_Pin,1);
	HAL_Delay(50);
	// read the feedback from the percharge relay to see if it is closed or not 
	if(HAL_GPIO_ReadPin(PRE_CHARGE_FB_GPIO_Port,PRE_CHARGE_FB_Pin)== 0)
	{
		// if the precharge relay is not closed then the relay  or its connection has a problem so call ERROR function
		ErrorAction();
	}


	// if dc90 from bamocar is set high this means that the inverter is precharged and now its time to go to neutral state
	if(HAL_GPIO_ReadPin(DC90_INPUT_GPIO_Port,DC90_INPUT_Pin))
	{
				nextStateM=NEUTRAL;

	}
	//else the inverter is still precharging
	else   
	{
			nextStateM=PRECHARGE;
	}
	currStateM=nextStateM;

}


void NEUTRAL_Func()
{
	//open the precharge relay the inverter is charged now
	HAL_GPIO_WritePin(PRECHARGE_RELAY_GPIO_Port,PRECHARGE_RELAY_Pin,0);

	//close the AIR+ve relay
	HAL_GPIO_WritePin(AIR_POSITIVE_GPIO_Port,AIR_POSITIVE_Pin,1);

	HAL_Delay(50); //just a delay to make sure that the relays had time to act

	if(HAL_GPIO_ReadPin(PRE_CHARGE_FB_GPIO_Port,PRE_CHARGE_FB_Pin)== 1)
	{
		// if the precharge relay is not opened then the relay  or its connection has a problem so call ERROR function
		ErrorAction();
	}

	if(HAL_GPIO_ReadPin(AIR_POSITIVE_FB_GPIO_Port,AIR_NEGATIVE_FB_Pin)==0)
	{
		//if the AIR+ve relay is not closed then there is a a problem in the relay or its connection
		ErrorAction();
	}

	if(HAL_GPIO_ReadPin(START_BTN_GPIO_Port,START_BTN_Pin))
	{
		// IF THE START BUTTON IS PRESSED GO TO DISCHARGE STATE
		while(HAL_GPIO_ReadPin(START_BTN_GPIO_Port,START_BTN_Pin)); //wait until the driver release the button
		HAL_Delay(50); //delay for button debouncing
		nextStateM=DISCHARGE;

	}

	else if(HAL_GPIO_ReadPin(RTD_BTN_GPIO_Port,RTD_BTN_Pin) && val[2]>VAL_BRAKE_ANGLE_RTD)
	{	
		// if the RTD button is pressed then do the next checks

		uint32_t time_on_press=HAL_GetTick(); //store the value when the key is pressed
		uint32_t time_difference=HAL_GetTick()-time_on_press;  //difference between when key is pressed ad current time
		while( (time_difference<3000) && (HAL_GPIO_ReadPin(RTD_BTN_GPIO_Port,RTD_BTN_Pin)) &&  (val[2]>VAL_BRAKE_ANGLE_RTD) )
		{
			//this while is broken when the rtd button is released before 3 seconds or the brakes pedal is released before 3 seconds
			time_difference=HAL_GetTick()-time_on_press;
		}

		//if the rtd btn is pressed with the brakes for 3 seconds then the next state is drive mode
		if(time_difference>=3000)
		{
			//make the rtd sound for 3 seconds
			HAL_GPIO_WritePin(RTDS_GPIO_Port,RTDS_Pin,1);
			HAL_Delay(3000);
			HAL_GPIO_WritePin(RTDS_GPIO_Port,RTDS_Pin,0);

			//wait until the rtd button is released
			while(HAL_GPIO_ReadPin(RTD_BTN_GPIO_Port,RTD_BTN_Pin));
			HAL_Delay(50); //small delay for button debouncing
			nextStateM=DRIVE;
		}
	}
	else
	{
		nextStateM=NEUTRAL;
	}

	currStateM=nextStateM;
}



void DRIVE_Func()
{

	//The motor inverter enables
	HAL_GPIO_WritePin(RFE_ENABLE_GPIO_Port,RFE_ENABLE_Pin,1);
	HAL_GPIO_WritePin(DRIVE_ENABLE_GPIO_Port,DRIVE_ENABLE_Pin,1);

	//read the value of APPS
	uint16_t APPS_READ=uint16_t_Read_APPS();

	//MAPS THA ADC READ TO PWM OUTPUT VALUE
	APPS_READ=map(APPS_READ,0,4095,0,PWM_MAX_OUTPUT);
	//OUTPUTS THE TORQUE COMMAND AS PWM
	htim3.Instance->CCR3=APPS_READ;


	if(HAL_GPIO_ReadPin(START_BTN_GPIO_Port,START_BTN_Pin))
	{
		// IF THE START BUTTON IS PRESSED GO TO DISCHARGE STATE
		while(HAL_GPIO_ReadPin(START_BTN_GPIO_Port,START_BTN_Pin)); //wait until the driver release the button
		HAL_Delay(50); //delay for button debouncing
		

		htim3.Instance->CCR3=0;
		nextStateM=DISCHARGE;

	}

	else
	{
		nextStateM=DRIVE;
	}
	currStateM=nextStateM;


}


void DISCHARGE_Func()
{

	
	HAL_GPIO_WritePin(EVMS_RELAY_GPIO_Port,EVMS_RELAY_Pin,0);

	//disable the inverter
	HAL_GPIO_WritePin(RFE_ENABLE_GPIO_Port,RFE_ENABLE_Pin,0);
	HAL_GPIO_WritePin(DRIVE_ENABLE_GPIO_Port,DRIVE_ENABLE_Pin,0);


	//open the AIR+ve relay
	HAL_GPIO_WritePin(AIR_POSITIVE_GPIO_Port,AIR_POSITIVE_Pin,0);
if(HAL_GPIO_ReadPin(AIR_POSITIVE_FB_GPIO_Port,AIR_NEGATIVE_FB_Pin)==1)
	{
		//if the AIR+ve relay is not opened then there is a a problem in the relay or its connection
		ErrorAction();
	}


	if(HAL_GPIO_ReadPin(DC60_INPUT_GPIO_Port,DC60_INPUT_Pin)==1)
	{
		nextStateM=IDLE;
	}
	else
	{
		nextStateM=DISCHARGE;
	}
	currStateM=nextStateM;

}




void loop()
{
	switch(currStateM)
	{
		case IDLE:
			IDLE_Func();
			break;

		case PRECHARGE:
			PRECHARGE_Func();
			break;

		case NEUTRAL:
			NEUTRAL_Func();
			break;

		case DRIVE:
			DRIVE_Func();
			break;

		case DISCHARGE:
			DISCHARGE_Func();
			break;
	}
}




void ErrorAction()
{
	//open the shutdown circuit and go in infinite loop
	HAL_GPIO_WritePin(EVMS_RELAY_GPIO_Port,EVMS_RELAY_Pin,1);
	while(1);
}
