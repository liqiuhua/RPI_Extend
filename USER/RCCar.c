#include "PWM_out_in.h"
#include "stdio.h"
#include "RCCar.h"
#include "RGB_LED.h"
#define CAR_GO_AHEAD_SERVO_VALUE   2000
#define CAR_LEFT(value)  ((value<(CAR_GO_AHEAD_SERVO_VALUE-5))&&(value>1000))
#define CAR_RIGHT(value) ((value>(CAR_GO_AHEAD_SERVO_VALUE+5))&&(value<3000))
#define CAR_FORWARD     1
#define CAR_BACKWARD    2
#define RC_MAX_VALUE 15200
#define RC_MID_VALUE 12000
#define RC_MIN_VALUE 8800


struct _RC_Control{
    uint16_t ELEV;
    uint16_t AILE;
    uint16_t THRO;
    uint16_t RUDD;
    uint16_t GEAR;
    uint16_t AUX1;
    uint16_t AUX2;
    uint16_t AUX3;
}RC_Control_data;
struct _RCCarCortol{
	uint16_t throttle;
	uint16_t left;
	uint16_t right;
	uint8_t travelDirection;
}RCCarCortol;
static void RCCar_Contorl(struct _RCCarCortol * carCortol);
static void RC_Control_data_Deal(void);
static void RC_Control_data_get(void);
TaskHandle_t xHandleTaskRC=NULL;
void vRCStart(void *pvParameters)
{
    PWM_OUT_1_4_Init();
    PWM_OUT_5_8_Init();
    PWM_IN_1_4_Init();
    PWM_IN_5_8_Init();

    while(1)
    {
        vTaskDelay(10);
        RC_Control_data_get();
        RC_Control_data_Deal();
        RCCar_Contorl(&RCCarCortol);
    }
    
}
uint16_t getRCControlData(uint8_t ch)
{
    switch(ch){
    case THROTTLE_CH:   return RCCarCortol.throttle;
    case LEFT_CH :      return RCCarCortol.left;
    case RIGHT_CH:      return RCCarCortol.right;
    case TRAVEL_DIRECTION_CH:return  RCCarCortol.travelDirection;
    default:break;
    }
    return 0;
}
static void RC_Control_data_get(void)
{
    RC_Control_data.ELEV = getPWM_IN_1_4_ICValue(3);
    RC_Control_data.AILE = getPWM_IN_1_4_ICValue(2);
    RC_Control_data.THRO = getPWM_IN_1_4_ICValue(1);
    RC_Control_data.RUDD = getPWM_IN_1_4_ICValue(0);
    RC_Control_data.GEAR = getPWM_IN_5_8_ICValue(0);
    RC_Control_data.AUX1 = getPWM_IN_5_8_ICValue(2);
    RC_Control_data.AUX2 = getPWM_IN_5_8_ICValue(3);
    RC_Control_data.AUX3 = getPWM_IN_5_8_ICValue(1);
}
#define CAR_SERVO_MID_VALUE   13000
#define CAR_SERVO_MIN_VALUE   9000
#define CAR_SERVO_MAX_VALUE   17000
#define CAR_SERVO(value)  (value<=(CAR_SERVO_MID_VALUE-CAR_SERVO_MIN_VALUE))

static void RC_Control_data_Deal(void)
{
    if(RC_Control_data.AUX2>(RC_MID_VALUE+1000))
	{
		RCCarCortol.travelDirection=CAR_BACKWARD;
		RGB_LED_Set(1,0,0);
	}
	else if(RC_Control_data.AUX2<(RC_MID_VALUE-1000))
	{
		RCCarCortol.travelDirection=CAR_FORWARD;
        RGB_LED_Set(0,1,0);
	}
    if(RC_Control_data.THRO>(RC_MIN_VALUE+200))
	{
		RCCarCortol.throttle= (RC_Control_data.THRO-RC_MIN_VALUE)/100*312;
	}
	else
	{
		RCCarCortol.throttle=0;
	}
    
    	if(RC_Control_data.ELEV>(RC_MID_VALUE+100))
	{
		RCCarCortol.left = (RC_Control_data.ELEV-RC_MID_VALUE)*10/8;
		if(!CAR_SERVO(RCCarCortol.left))
		{
			RCCarCortol.left=4000;
		}
		RCCarCortol.right = 0;
	}
	else if(RC_Control_data.ELEV<(RC_MID_VALUE-100))
	{
		RCCarCortol.left = 0;
		RCCarCortol.right = (RC_MID_VALUE-RC_Control_data.ELEV)*10/8 ;
		if(!CAR_SERVO(RCCarCortol.right))
		{
			RCCarCortol.right=4000;
		}
        
	}
	else
	{
		RCCarCortol.left = 0;
		RCCarCortol.right = 0;
	}
    
}
static void RCCar_Contorl(struct _RCCarCortol * carCortol)
{
    if(CAR_FORWARD==RCCarCortol.travelDirection)
    {
        PWM_OUT_1_4_out(0x02,0);
        PWM_OUT_1_4_out(0x01,carCortol->throttle);
    }
    else if(CAR_BACKWARD==RCCarCortol.travelDirection)
    {
        PWM_OUT_1_4_out(0x01,0);
        PWM_OUT_1_4_out(0x02,carCortol->throttle);
    }
    else
    {
        PWM_OUT_1_4_out(0x01,0);
        PWM_OUT_1_4_out(0x02,0);
    }
		if(CAR_SERVO(carCortol->left)&&CAR_SERVO(carCortol->right))
		{
			if((carCortol->left))
			{
					PWM_OUT_5_8_out(0x01,CAR_SERVO_MID_VALUE-carCortol->left);        
			}
			else if((carCortol->right))
			{
					 PWM_OUT_5_8_out(0x01,(carCortol->right+CAR_SERVO_MID_VALUE));  
			}
			else
			{
				PWM_OUT_5_8_out(0x01,CAR_SERVO_MID_VALUE); 
			}
		}
		else
		{
			 PWM_OUT_5_8_out(0x01,CAR_SERVO_MID_VALUE);  
		}
}
