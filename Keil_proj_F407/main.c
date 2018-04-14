#include "stm32f4xx.h" 
#include "as5048.h"

                 // Device header
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"
#include "mylib.h"
#include "init.h"
#include "motor.h"

//#include "tm_stm32f4_delay.h"
	
float angle, angle_error, angle_test;
float des_val,des_val1;
uint32_t t1, t2, t3, t4, dt1, dt22, p;

float voltage, current;



// moving average filter variables


uint8_t filled_ADC;
	uint16_t i_ADC; // counter for filling in
	float data_ADC;
	float arr_ADC[window_ADC],  angle_average, a_i_ADC,  des_val_raw; // variables for first order moving average
	uint16_t k_ADC; // counter
	uint32_t ADC_average;
	uint8_t flag_ADC;
  uint32_t sum_ADC;





int main(void)
	
{
	
	
	
	
	SPI3_ini();
	
	
	TIM5_ini(); // Delay timer
	
	led15_ini();
	
	
	BLDC_PWMTimerInit(); // init PWM timer
	
	
	TIM4_ini(); // PWM LED Visualisation timer
	PWM_ENx_ini();// PWM LED Visualisation
	
	ADC_initt();
	//Set_nRes_nSleep();
	//GPIO_SetBits(GPIOA, GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3); // EN1,2,3 to 1 enable all half-bridges
	FOC_InitPosition();
	
	
	
	
	
		des_val = 30; ///////////////





	
	while(1)
	{
	

	
	
	t1 = TIM5->CNT;
	angle = CQ_average_angle();//ThirdOrder_average();//average_angle();

		
	des_val = (float)ADC_average*360/4095;
		
	angle_error = des_val - angle;

	FOC(angle, angle_error, 0.2, 0.5)	;

		t2 = TIM5->CNT;
	  dt1 = t2 - t1;
	

		
	
	}
}













void ADC_IRQHandler()
	{
		if(ADC_GetITStatus(ADC1,ADC_IT_EOC) !=RESET)
		{
			
			
			ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
			
			// averaging	
		if(!filled_ADC)
		{
			
			
				arr_ADC[i_ADC] = ADC_GetConversionValue(ADC1) ;
				sum_ADC = sum_ADC + arr_ADC[i_ADC];
				if(i_ADC < window_ADC - 1) 
				{
					i_ADC++;
				}
				else
				{
					ADC_average  = sum_ADC / (uint32_t)window_ADC ; // out of the filter
					filled_ADC = 1;
					k_ADC=0;
					
				}
			 
		}
		
		// 2) start filtering
		
		else
		{
			a_i_ADC = ADC_GetConversionValue(ADC1) ;
			des_val_raw = a_i_ADC*360/4095;
		//	flag_ADC = 1;
			sum_ADC = sum_ADC - arr_ADC[k_ADC] + a_i_ADC;
			ADC_average  = sum_ADC / (uint32_t)window_ADC ; // out of the filter
			arr_ADC[k_ADC] = a_i_ADC; // substitute thrown out value with new value for cycling
			k_ADC++;
			if(k_ADC >= window_ADC) k_ADC=0; // array loop
			
			
		}
		
		 
		
			//Speed = (float)(ADC_GetConversionValue(ADC1))*6/4095; // used for potentiometr speed control
		//	des_val_raw = ADC_GetConversionValue(ADC1);//*360/4095; // used for potentiometr angle tracking
			
			
			
			//alpha = (float)(ADC_GetConversionValue(ADC1))*360/4095;
			
			ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_480Cycles);
	    ADC_SoftwareStartConv(ADC1);
			//p++;
			
		}
		
	}  
	
	
	
	
	
	



