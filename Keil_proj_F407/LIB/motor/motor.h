#ifndef MOTOR_H
#define MOTOR_H

#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "init.h"
#include "arm_math.h"
#include "as5048.h"

#define High			0x01
#define Low				0x00
#define average		 100
#define Pole_Pairs 15//12
#define Vdc 				12
#define Pi 3.1415926535897932384
#define CALIBRATION_MODE 1
#define SINE_STEPS 20000



#define DISABLED_MODE 0x00
#define SINE_MODE 		0x1
#define STATIC_MODE 	0x2




	// PA1 - EN1
	// PA2 - EN2  (nReset)
	// PA3 - EN3 (EN2)
	// PA4 - nSLEEP
	// PA5 - nRESET (EN3)
	// IN1(PWM1) - PD12
	// IN2(PWM2) - PD13
	// IN3(PWM3) - PD14









void Use_HalfBridge(int num, int Transistor, int power); // num - 1,2,3;  Switch - High or Low; power - duty cycle
void dead_time(uint32_t time);
void Set_nRes_nSleep(void);
void Change_winding(void);



void rotate_forv(void);
void rotate_back(void);
void sine_PWM_ini(void);
//float average_angle(uint16_t raw_angle);


void FOC_InitPosition(CQ_average_filter_typedef* filter);
void FOC(float angle, float error_angle, float K_p, float K_d, float K_i);



void sinus_control(float des_val_);
void sinus_control_V2(float err);



void OpenLoop_contro(float des_val_);






#endif
