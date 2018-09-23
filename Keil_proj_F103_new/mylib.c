#include "mylib.h"







//  BLDC_PWMTimerInit();
//	
//	TIM_SelectOCxM(TIM1, TIM_Channel_1, TIM_OCMode_PWM1);
//	TIM_SelectOCxM(TIM1, TIM_Channel_2, TIM_OCMode_PWM1);
//	TIM_SelectOCxM(TIM1, TIM_Channel_3, TIM_OCMode_PWM1);
//	
//	
//	
//		TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Enable);
//		TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Enable);
//	
//		TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Enable);
//		TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Enable);
//	
//		TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Enable);
//		TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Enable);









void TIM4_ini(void) /// Time measuring timer
{
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
		//base settings
	TIM_TimeBaseInitTypeDef TIM4_Base;
	TIM4_Base.TIM_Period = 0xFFFF;
  TIM4_Base.TIM_Prescaler = 18000-1; // 1kHz
  TIM4_Base.TIM_ClockDivision = TIM_CKD_DIV4 ; //
  TIM4_Base.TIM_CounterMode = TIM_CounterMode_Up;
  TIM4_Base.TIM_RepetitionCounter = 0x0000;
	TIM_TimeBaseInit(TIM4, &TIM4_Base);
	TIM_Cmd(TIM4, ENABLE);
}




//Delay


uint32_t time1;

/*
void myDelay_microsec(uint32_t delay)
{
	time1 = TIM4->CNT;
	while( ((TIM4->CNT) - time1) < delay) {}
}
*/

void myDelay_ms(uint32_t delay)
{
	time1 = TIM4->CNT;
	while( ((TIM4->CNT) - time1) < delay*4) {}
	
}
	


float Vq;
float	Vd;
float Va, Vb, Vc, Va_1, Vb_1, Vc_1;
float theta, theta_elec_degrees;
float Vinv1,Vinv2, Vinv3;
float  error_angle_last;
float error_in_proc, er_mem, angle_mem;
extern float angle_init , angle ;

uint32_t PWM1, PWM2, PWM3;

void FOC(float angle, float error_angle, float K_p, float K_d)
{
	theta_elec_degrees = ((angle - angle_init)*PolePairs + 90 ); // 11 - pole pairs (22P). + 90 because at initial position theta = 90  
	theta = theta_elec_degrees*0.01745329251994329576923690768489 ;//Pi/180; // translating into radians
	 
	
	Vd = 0; // !
	
	if(error_angle > 180)
	{
		error_angle = 360 - error_angle;
		error_angle = - error_angle;
	}
	if(error_angle < -180)
	{
		error_angle = 360 + error_angle;
		//error_angle = - error_angle;
	}
	
	
	error_in_proc = error_angle;
	if ((error_angle > 100)||(error_angle< -100)) 
	{
		er_mem = error_angle;
		angle_mem = angle;
	}
	
	//Vq max - 15V
	Vq = K_p*error_angle  ;//+ (error_angle - error_angle_last)*K_d; //Speed; //
//	error_angle_last = error_angle;
	
	
	
	if(Vq < -(Vdc/2)) Vq = -(Vdc/2); // 6V = Vdc/2 , voltage limitation
	if(Vq > (Vdc/2)) Vq = (Vdc/2);
	
	
	
	Va_1 = cos(theta);//cos(theta         );     
	Vb_1 = cos(theta - 2.0943951023931954923084289221863);//cos(theta - 2.0943951023931954923084289221863 /* 2*Pi/3 */);
	Vc_1 = cos(theta + 2.0943951023931954923084289221863);//cos(theta + 2.0943951023931954923084289221863);
	
	
	Va = Va_1 * Vq; // projection calculation of Vq into A phase
	Vb = Vb_1 * Vq; // projection calculation of Vq into B phase
	Vc = Vc_1 * Vq; // projection calculation of Vq into C phase
	
	Vinv1 = Va + (Vdc/2); // Obtaining value for invertor, +6 because Vinv relates with V_phase as Vinv = Vphase + Vdc/2 in order to avoid negative values for invertor voltage.
	Vinv2 = Vb + (Vdc/2); // should also be taken into account that Vphase(max) = Vdc/2 (with sine PWM) 
	Vinv3 = Vc + (Vdc/2);
	
	// Vinx_max = 20V, PWM = Vinv*PWM_period/Vinv_max
	
	
	
	TIM1->CCR1 = (uint32_t)(Vinv1*4500/Vdc)  ; 
  TIM1->CCR2 = (uint32_t)(Vinv2*4500/Vdc)  ;
  TIM1->CCR3 = (uint32_t)(Vinv3*4500/Vdc)  ;
	
	PWM1 = TIM1->CCR1;
	PWM2 = TIM1->CCR2;
	PWM3 = TIM1->CCR3;
}


/*

void ADC_initt(void) // PB1
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOB , ENABLE);
	
	
	
	GPIO_InitTypeDef GPIO_AI;
	GPIO_StructInit(&GPIO_AI);
	GPIO_AI.GPIO_Pin = GPIO_Pin_1;
	GPIO_AI.GPIO_Mode = GPIO_Mode_AIN;
	//GPIO_AI.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//GPIO_AI.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_AI);
	
	
	
	
	ADC_InitTypeDef ADC_InitStructure;

	ADC_StructInit(&ADC_InitStructure);
	
	
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	NVIC_EnableIRQ(ADC1_2_IRQn);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_7Cycles5);
	ADC_Cmd (ADC1,ENABLE);
	ADC_SoftwareStartConvCmd ( ADC1 , ENABLE ) ;
	
}
*/


void SPI_ini(void)
{
	// PA5 - SPI_SCK
	// PA6 - SPI_MISO
	//PA7 - SPI_MOSI
	// PB0 - CS
	
	
	
}
	
	