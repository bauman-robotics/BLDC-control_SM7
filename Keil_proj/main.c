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
	PWM_IN();
	// ADC Init
	ADC_DMA_init();
	// TIM1, outputs, inputs, interrupts, etc. Init
//	BLDC_Init();
	//ADC_initt();
	TIM4_ini(); //delay timer
	
	
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
		
		
		
		
		
		RCC_ClocksTypeDef Clockss;
		;
		 
	 RCC_GetClocksFreq(&Clockss);
	 ADCCLK_Freq = Clockss.ADCCLK_Frequency;
		HCLK_Freq = Clockss.HCLK_Frequency;
		PCLK1_Freq = Clockss.PCLK1_Frequency;
		 PCLK2_Freq = Clockss.PCLK2_Frequency;
		SYSCLK_Freq = Clockss.SYSCLK_Frequency;
		
		
	
	// Reverse pin Init
//	GPIO_InitTypeDef  GPIO_InitStructure;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOB, GPIO_Pin_0);


/*

	TIM1->CCR1 = 4500;
	TIM1->CCR2 = 2000;
	TIM1->CCR3 = 3000;
	
	*/
	
	
	
	
	
	
	
	// FOC init
	
	
	/*//Vdc = 22; //V
	TIM1->CCR1 = (uint32_t)(Vdc*BLDC_CHOPPER_PERIOD/Vdc) ; //x = Vdc  
  TIM1->CCR2 = (uint32_t)((Vdc/4)*BLDC_CHOPPER_PERIOD/Vdc)  ;// x = - Vdc/4 + Vdc/2  
  TIM1->CCR3 = (uint32_t)((Vdc/4)*BLDC_CHOPPER_PERIOD/Vdc)  ; //x = - Vdc/4 + Vdc/2
	
	myDelay_ms(3000);	*/
	
	angle_init = 92.8;//angle_average;//angle_IRQ; //190.366;//angle_IRQ;











	
	
	
	
	// Sine without feedback
	
	
	uint8_t Sine_Amp = 40; //   % of the total value of PWM period; // sine amp for simple mode rotation (scalar)
	
	uint8_t pwmSin[] = 
		 
		 {128, 132, 136, 140, 143, 147, 151, 155, 159, 162, 166, 170, 174, 178, 181, 185, 189, 192, 196, 200, 203, 207, 211, 214, 218, 221, 225, 228, 232, 235,
			 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 248, 249, 250, 250, 251, 252, 252, 253, 253, 253, 254, 254, 254, 255, 255, 255, 255, 255, 255,
			 255, 255, 255, 255, 255, 255, 255, 254, 254, 254, 253, 253, 253, 252, 252, 251, 250, 250, 249, 248, 248, 247, 246, 245, 244, 243, 242, 241, 240, 239,
			 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 248, 249, 250, 250, 251, 252, 252, 253, 253, 253, 254, 254, 254, 255, 255, 255, 255, 255, 255,
			 255, 255, 255, 255, 255, 255, 255, 254, 254, 254, 253, 253, 253, 252, 252, 251, 250, 250, 249, 248, 248, 247, 246, 245, 244, 243, 242, 241, 240, 239, 
			 238, 235, 232, 228, 225, 221, 218, 214, 211, 207, 203, 200, 196, 192, 189, 185, 181, 178, 174, 170, 166, 162, 159, 155, 151, 147, 143, 140, 136, 132,
			 128, 124, 120, 116, 113, 109, 105, 101, 97, 94, 90, 86, 82, 78, 75, 71, 67, 64, 60, 56, 53, 49, 45, 42, 38, 35, 31, 28, 24, 21, 18, 17, 16, 15, 14,
			 13, 12, 11, 10, 9, 8, 8, 7, 6, 6, 5, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5, 6, 6, 7, 8, 8, 9, 10,
			 11, 12, 13, 14, 15, 16, 17, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 8, 7, 6, 6, 5, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			 2, 2, 2, 3, 3, 3, 4, 4, 5, 6, 6, 7, 8, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 21, 24, 28, 31, 35, 38, 42, 45, 49, 53, 56, 60, 64, 67, 71, 75, 78,
			 82, 86, 90, 94, 97, 101, 105, 109, 113, 116, 120, 124};
		 
	
	uint16_t increment = 0;
			 
			 
	sineArraySize = sizeof(pwmSin)/sizeof(uint8_t); // Find lookup table size
  uint8_t phaseShift = sineArraySize / 3;         // Find phase shift and initial A, B C phase values
  currentStepA = 0;
  currentStepB = currentStepA + phaseShift;
  currentStepC = currentStepB + phaseShift;
 
  sineArraySize--;
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*
	// determining pole pairs with relation between real angle and one electrical rotation

 for(int i=0; i<360; i++)
 {
	 if(!i)
	 {
		 TIM1->CCR1 = (uint32_t)((pwmSin[currentStepA]*20*Sine_Amp)/100) ; // 4 - = (total period of PWM) / (max table value) , (Sine_amp)/(100) allows to adjust sine amplitude 
  TIM1->CCR2 = (uint32_t)((pwmSin[currentStepB]*20*Sine_Amp)/100) ;
  TIM1->CCR3 = (uint32_t)((pwmSin[currentStepC]*20*Sine_Amp)/100) ;  
  
      
 
  currentStepA = currentStepA + 1;
  currentStepB = currentStepB + 1;
  currentStepC = currentStepC + 1;
		
 
  //Check for lookup table overflow and return to opposite side if necessary
  if(currentStepA > sineArraySize)  currentStepA = 0;
  if(currentStepA < 0)  currentStepA = sineArraySize;
 
  if(currentStepB > sineArraySize)  currentStepB = 0;
  if(currentStepB < 0)  currentStepB = sineArraySize;
 
  if(currentStepC > sineArraySize)  currentStepC = 0;
  if(currentStepC < 0) currentStepC = sineArraySize; 
  
  /// Control speed by this delay
  myDelay_ms(5000);
	angle1 = angle_IRQ;
	
	 }
	 else
	 {
	TIM1->CCR1 = (uint32_t)((pwmSin[currentStepA]*12*Sine_Amp)/100) ; // 4 - = (total period of PWM) / (max table value) , (Sine_amp)/(100) allows to adjust sine amplitude 
  TIM1->CCR2 = (uint32_t)((pwmSin[currentStepB]*12*Sine_Amp)/100) ;
  TIM1->CCR3 = (uint32_t)((pwmSin[currentStepC]*12*Sine_Amp)/100) ;  
  
      
 
  currentStepA = currentStepA + 1;
  currentStepB = currentStepB + 1;
  currentStepC = currentStepC + 1;
		
 
  //Check for lookup table overflow and return to opposite side if necessary
  if(currentStepA > sineArraySize)  currentStepA = 0;
  if(currentStepA < 0)  currentStepA = sineArraySize;
 
  if(currentStepB > sineArraySize)  currentStepB = 0;
  if(currentStepB < 0)  currentStepB = sineArraySize;
 
  if(currentStepC > sineArraySize)  currentStepC = 0;
  if(currentStepC < 0) currentStepC = sineArraySize; 
  
  /// Control speed by this delay
  	myDelay_ms(10);	
	
		 
	 }
	 
 
	 
	 
	 
 }
	
	angle2 = angle_IRQ;
 d_angle = angle2 - angle1;
	
	
	
	TIM1->CCR1 = 0 ; // 4 - = (total period of PWM) / (max table value) , (Sine_amp)/(100) allows to adjust sine amplitude 
  TIM1->CCR2 = 0 ;
  TIM1->CCR3 = 0;
	
	
	
	
	
	
	
	
	
	/*
	TIM1->CCR1 = (uint32_t)((pwmSin[currentStepA]*20*Sine_Amp)/100) ; // 4 - = (total period of PWM) / (max table value) , (Sine_amp)/(100) allows to adjust sine amplitude 
  TIM1->CCR2 = (uint32_t)((pwmSin[currentStepB]*20*Sine_Amp)/100) ;
  TIM1->CCR3 = (uint32_t)((pwmSin[currentStepC]*20*Sine_Amp)/100) ;  
	*/
	  
	
	des_val = 30;
	
myDelay_ms(1000);


    while(1)
    {
			
			
		//		averaging adc values
			
			cnttt++;
			
			if(flag_ADC == 1)
			{
			sum = sum - arr[k] + a_i;
			ADC_average  = sum / window ; // out of the filter
			arr[k] = a_i; // substitute thrown out value with new value for cycling
			k++;
			if(k >= window) k=0; // array loop
			flag_ADC = 0;
			}
			
			
			angle = angle_IRQ;
			des_val = (ADC_average)*360/4095;
			angle_error = des_val - angle;
			FOC(angle, angle_error, 0.5, 0.5);
			
			
			
			
			


			
			
			
			
			
			
			
			
			
			
			
			
			/*
			
			// Just rotating
		
		TIM1->CCR1 = (uint32_t)((pwmSin[currentStepA]*20*Sine_Amp)/100); // 4 - = (total period of PWM) / (max table value) , (Sine_amp)/(100) allows to adjust sine amplitude 
  TIM1->CCR2 = (uint32_t)((pwmSin[currentStepB]*20*Sine_Amp)/100) ;
  TIM1->CCR3 = (uint32_t)((pwmSin[currentStepC]*20*Sine_Amp)/100);  
  
      
 
  currentStepA = currentStepA + 1;
  currentStepB = currentStepB + 1;
  currentStepC = currentStepC + 1;
		
 
  //Check for lookup table overflow and return to opposite side if necessary
  if(currentStepA > sineArraySize)  currentStepA = 0;
  if(currentStepA < 0)  currentStepA = sineArraySize;
 
  if(currentStepB > sineArraySize)  currentStepB = 0;
  if(currentStepB < 0)  currentStepB = sineArraySize;
 
  if(currentStepC > sineArraySize)  currentStepC = 0;
  if(currentStepC < 0) currentStepC = sineArraySize; 
  
  /// Control speed by this delay
  myDelay_ms(1);
			
		*/	
			
			
			
			
			
			
			














			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
//    	if (ADCBuffer[0] > BLDC_ADC_START) {
//    		if (BLDC_MotorGetSpin() == BLDC_STOP) {
//    			// Check Reverse pin
//    			if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) != 0) {
//    				// Forward
//    				BLDC_MotorSetSpin(BLDC_CW);
//    			}
//    			else {
//    				// Backward
//    				BLDC_MotorSetSpin(BLDC_CCW);
//    			}
//    			BLDC_MotorCommutation(BLDC_HallSensorsGetPosition());
//    		}
// 
//            
//            BLDC_SetPWM(BLDC_ADCToPWM(ADCBuffer[0]));
//    	}
//    	else {
//    		if (BLDC_MotorGetSpin() != BLDC_STOP) {
//    			if (ADCBuffer[0] < BLDC_ADC_STOP) {
//    				BLDC_MotorStop();
//    			}
//    		}
//    	}
    }
}


void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
  {
		//cnt++;
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
    NVIC_DisableIRQ(TIM2_IRQn);

    
    period = TIM_GetCapture1(TIM2);
   
		 duty_cycle = TIM_GetCapture2(TIM2);
		
		
    
		
		
		//angle = (duty_cycle/period)*360;
	//	x1 = (duty_cycle*360/65535);
		angle_IRQ = ((float)duty_cycle/period)*360;
		
		
	// averaging	// needs to be done with circle quantities technique , because of 0->360 step
/*	
		if(!filled)
		{
			
			
				arr[i] = angle_IRQ;
				sum = sum + arr[i];
				if(i < window-1) 
				{
					i++;
				}
				else
				{
					angle_average  = sum / window ; // out of the filter
					filled = 1;
					k=0;
					
				}
			 
		}
		
		// 2) start filtering
		
		else
		{
			a_i = angle_IRQ;
			sum = sum - arr[k] + a_i;
			angle_average  = sum / window ; // out of the filter
			arr[k] = a_i; // substitute thrown out value with new value for cycling
			k++;
			if(k >= window) k=0; // array loop
			
			
		}
		*/
		
		
		
		
		

    NVIC_EnableIRQ(TIM2_IRQn);

    

    if (TIM_GetFlagStatus(TIM2, TIM_FLAG_CC1OF) != RESET) // if edge was captured during hadler processing
    {
      TIM_ClearFlag(TIM2, TIM_FLAG_CC1OF);
      // ...
    }
  }
}  

/*
void ADC_IRQHandler()
	{
		if(ADC_GetITStatus(ADC1,ADC_IT_EOC) !=RESET)
		{
			ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
			//Speed = (float)(ADC_GetConversionValue(ADC1))*6/4095; // used for potentiometr speed control
			des_val = (float)ADC_GetConversionValue(ADC1)*360/4095; // used for potentiometr angle tracking
			
			
			
			//alpha = (float)(ADC_GetConversionValue(ADC1))*360/4095;
			
			ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_7Cycles5);
	    ADC_SoftwareStartConvCmd ( ADC1 , ENABLE ) ;
			//p++;
		}
	}  
*/



void DMA1_Channel1_IRQHandler(void)
{
   DMA_ClearITPendingBit( DMA1_IT_TC1);
   DMA_ITConfig(DMA1_Channel1, DMA1_IT_TC1, DISABLE);

  // averaging	
		if(!filled)
		{
			
			
				arr[i] = ADCBuffer[0] ;
				sum = sum + arr[i];
				if(i < window - 1) 
				{
					i++;
				}
				else
				{
					ADC_average  = sum / window ; // out of the filter
					filled = 1;
					k=0;
					
				}
			 
		}
		
		// 2) start filtering
		
		else
		{
			a_i = ADCBuffer[0] ;
			flag_ADC = 1;
			
			
		}
		
		
		

   DMA_ITConfig(DMA1_Channel1, DMA1_IT_TC1, ENABLE);

   

}

