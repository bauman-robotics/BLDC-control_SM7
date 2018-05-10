#include "stm32f4xx.h" 
#include "as5048.h"

                 // Device header
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"
#include "mylib.h"
#include "init.h"
#include "motor.h"
#include <stdio.h>

//#include "tm_stm32f4_delay.h"
	
float angle, angle_error, angle_test;
float des_val,des_val1;
uint32_t t1, t2, t3, t4, dt1, dt22, p;

uint16_t ii;

float voltage, current;

uint16_t angle_raw_16;

// moving average filter variables


uint8_t filled_ADC;
	uint16_t i_ADC; // counter for filling in
	float data_ADC;
	float arr_ADC[window_ADC],  angle_average, a_i_ADC,  des_val_raw; // variables for first order moving average
	uint16_t k_ADC; // counter
	uint32_t ADC_average;
	uint8_t flag_ADC;
  uint32_t sum_ADC;


#define BLOCK_SIZE            1
#define NUM_TAPS              501


static float32_t firStateF32[BLOCK_SIZE + NUM_TAPS - 1];
/*
const float32_t firCoeffs32[NUM_TAPS] = { 
	
};*/
uint32_t blockSize = BLOCK_SIZE;
 float32_t outputF32;


uint32_t t_uart;
char send_uart;

char str[7];

int main(void)
	
{
	 //arm_fir_instance_f32 S;
	
	
//	arm_fir_init_f32(&S, NUM_TAPS, (float32_t *)&firCoeffs32[0], &firStateF32[0], blockSize);
	
	
	
	SPI3_ini();
	
	
	TIM5_ini(); // Delay timer
	
	led15_ini();
	
	
	BLDC_PWMTimerInit(); // init PWM timer
	
	
	TIM4_ini(); // PWM LED Visualisation timer
	PWM_ENx_ini();// PWM LED Visualisation
	
	ADC_initt();
	
	FOC_InitPosition();
	
	
//	USART_2_init();
	
	
	//	des_val = -71; ///////////////


//t_uart = TIM5->CNT;


	
	while(1)
	{
	

	
	
	t1 = TIM5->CNT;
		
	
	angle = CQ_average_angle();//CQ_average_angle();//CQ_IIRF_angle();//CQ_average_angle();//ThirdOrder_average();//average_angle();

		
		
		/*
		
		
		if(TIM5->CNT - t_uart > 10000)
		{
			while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET){}
				//send_uart = (char)(angle_raw_16>>8);
				//send_uart = 'f';
				sprintf(str,"%4d" , angle_raw_16 );
	        USART_SendData (USART2, str[0]);
				while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET){};
					USART_SendData (USART2, str[1]);
				while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET){};
					USART_SendData (USART2, str[2]);
				while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET){};
					USART_SendData (USART2, str[3]);
				while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET){};
				
					USART_SendData (USART2, 13);
				while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET){};
				
					
				/*
			while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET){}
				//send_uart = (char)(angle_raw_16&0xFF);
				sprintf((char*)str,"%04d", ii);
			USART_SendData (USART2, str )	;
				while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET){}
			USART_SendData (USART2, '\n')	; */
			
			/*
			t_uart = TIM5->CNT;
					ii++;
			
		}
		
		
		
	*/	
		
		
	//arm_fir_f32(&S, &angle, &outputF32, blockSize);	

		
	des_val = (float)ADC_average*360/4095 + 180;
		
	angle_error = des_val - angle;

	FOC(angle, angle_error, 0.3, 150)	;

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
	
	
	
	
	
	



