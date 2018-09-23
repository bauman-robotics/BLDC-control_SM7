#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include "misc.h"
#include "string.h"
#include "stdio.h"

#include "sysclk.h"
#include "adc_dma.h"
#include "bldc.h"
#include "mylib.h"



// moving average filter variables


uint8_t filled;
	uint16_t i; // counter for filling in
	float data, position;
	float arr[window], sum, angle_average, a_i; // variables for first order moving average
	uint16_t k; // counter
	uint16_t ADC_average;
	uint8_t flag_ADC;
















uint16_t currentStepA;
	uint16_t currentStepB;
	uint16_t currentStepC;
	uint16_t sineArraySize;
float des_val, angle_error;
uint32_t cnttt;

uint16_t period, duty_cycle, x1;

float angle_IRQ, angle_init, angle,  angle1, angle2, d_angle;
//uint8_t start, Vdc;

uint32_t ADCCLK_Freq, HCLK_Freq, PCLK1_Freq, PCLK2_Freq, SYSCLK_Freq;

uint16_t t1, t2, dt;

int main(void)









{
	// Set clock
	SetSysClockTo72();
	//PWM_IN();
	// ADC Init
	//ADC_DMA_init();
	//ADC_initt();
	TIM4_ini(); //delay timer
	SPI_ini();
	
	
	
	// Timer ini

	BLDC_PWMTimerInit();
	TIM_SelectOCxM(TIM1, TIM_Channel_1, TIM_OCMode_PWM1);
	TIM_SelectOCxM(TIM1, TIM_Channel_2, TIM_OCMode_PWM1);
	TIM_SelectOCxM(TIM1, TIM_Channel_3, TIM_OCMode_PWM1);
		
		TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Enable);
		TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Enable);
	
		TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Enable);
		TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Enable);
	
		TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Enable);
		TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Enable);
		
	
	des_val = 30;
	
myDelay_ms(1000);


    while(1)
    {
					
			//angle = angle_IRQ;
			des_val = (ADC_average)*360/4095;
			angle_error = des_val - angle;
			FOC(angle, angle_error, 0.5, 0.5);
			
			
			
			
			


			
			
			
			
			
			
			
			
			
			
			
			
		