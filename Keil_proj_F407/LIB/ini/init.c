#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "init.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"






void TIM4_ini(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_TimeBaseInitTypeDef timer_init;
	TIM_TimeBaseStructInit(&timer_init);
	timer_init.TIM_Period = PWM_period-1;// ---> 20kHz
	timer_init.TIM_Prescaler = 2-1; // ---> 42 MHz
	TIM_TimeBaseInit(TIM4, &timer_init);
	
	//channel 1;	
	TIM_OCInitTypeDef tim_oc_init1;
	TIM_OCStructInit(&tim_oc_init1);
	tim_oc_init1.TIM_Pulse = 0;  
	tim_oc_init1.TIM_OCMode = TIM_OCMode_PWM1;
	tim_oc_init1.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC1Init(TIM4, &tim_oc_init1);// 
	
	
	//channel 2;
	TIM_OCInitTypeDef tim_oc_init2;
	TIM_OCStructInit(&tim_oc_init2);
	tim_oc_init2.TIM_Pulse = 0;  
	tim_oc_init2.TIM_OCMode = TIM_OCMode_PWM1;
	tim_oc_init2.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC2Init(TIM4, &tim_oc_init2);// 
	
	//channel 3;
	TIM_OCInitTypeDef tim_oc_init3;
	TIM_OCStructInit(&tim_oc_init3);
	tim_oc_init3.TIM_Pulse = 0;  
	tim_oc_init3.TIM_OCMode = TIM_OCMode_PWM1;
	tim_oc_init3.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC3Init(TIM4, &tim_oc_init3);// 
	
	
	TIM_Cmd(TIM4, ENABLE);
	
	//	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);// Interrupts for Update
	//NVIC_EnableIRQ(TIM4_IRQn);
	
}



// PWM out for 12th pin

void PWM_ENx_ini(void) // INx, IN - PWMpins
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	
	
	//EN1 --> PD12--------------------------
	GPIO_InitTypeDef ledinit_AF;//
	GPIO_StructInit(&ledinit_AF);// 
	ledinit_AF.GPIO_Mode = GPIO_Mode_AF;//
	ledinit_AF.GPIO_Pin = GPIO_Pin_12;// 
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);// 
	GPIO_Init(GPIOD, &ledinit_AF);// 
	
	//EN2 --> PD13--------------------------
	GPIO_InitTypeDef ledinit_AF2;//
	GPIO_StructInit(&ledinit_AF2);// 
	ledinit_AF2.GPIO_Mode = GPIO_Mode_AF;//
	ledinit_AF2.GPIO_Pin = GPIO_Pin_13;// 
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);// 
	GPIO_Init(GPIOD, &ledinit_AF2);//
	
	
	//EN3 --> PD14--------------------------
	GPIO_InitTypeDef ledinit_AF3;//
	GPIO_StructInit(&ledinit_AF2);// 
	ledinit_AF3.GPIO_Mode = GPIO_Mode_AF;//
	ledinit_AF3.GPIO_Pin = GPIO_Pin_14;// 
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);// 
	GPIO_Init(GPIOD, &ledinit_AF3);//
		
}



void port_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	GPIO_InitTypeDef ledinit;
	GPIO_StructInit(&ledinit);
	ledinit.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5  ;
	ledinit.GPIO_Mode = GPIO_Mode_OUT;
	//GPIO_Init(GPIOC,&ledinit);
	GPIO_Init(GPIOA,&ledinit);
	
	
	//Pin 0 - Button
GPIO_InitTypeDef GPIO_InitDef;
GPIO_InitDef.GPIO_Pin = GPIO_Pin_0;
//Mode output
GPIO_InitDef.GPIO_Mode = GPIO_Mode_IN;
//Output type push-pull
GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
//With pull down resistor
GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_DOWN;
//50MHz pin speed
GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;
 
//Initialize pin on GPIOA port
GPIO_Init(GPIOA, &GPIO_InitDef);
	
	
	
	/*
	GPIO_InitTypeDef ledinit2;
	GPIO_StructInit(&ledinit2);
	ledinit2.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;
	ledinit2.GPIO_Mode = GPIO_Mode_OUT;*/
	

	
//	GPIO_Init(GPIOD, &ledinit2); // TENPORARY FOR TEST!!
	
	
}


void ADC_initt(void) // PB1
{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	GPIO_InitTypeDef GPIO_AI;
	GPIO_StructInit(&GPIO_AI);
	GPIO_AI.GPIO_Pin = GPIO_Pin_1;
	GPIO_AI.GPIO_Mode = GPIO_Mode_AN;
	GPIO_AI.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_AI.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_AI);
	
	
	
	ADC_CommonInitTypeDef ADC_init;
	ADC_InitTypeDef ADC_InitStructure;

	ADC_StructInit(&ADC_InitStructure);
	ADC_CommonStructInit(&ADC_init);
	ADC_CommonInit (&ADC_init);
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	NVIC_EnableIRQ(ADC_IRQn);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_480Cycles);
	ADC_SoftwareStartConv(ADC1);
	
}


void PWM_INx_ini(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	
	
	//IN1 --> PD12--------------------------
	GPIO_InitTypeDef ledinit_AF;//
	GPIO_StructInit(&ledinit_AF);// 
	ledinit_AF.GPIO_Mode = GPIO_Mode_AF;//
	ledinit_AF.GPIO_Pin = GPIO_Pin_12;// 
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);// 
	GPIO_Init(GPIOD, &ledinit_AF);// 
	
	//IN2 --> PD13--------------------------
	GPIO_InitTypeDef ledinit_AF2;//
	GPIO_StructInit(&ledinit_AF2);// 
	ledinit_AF2.GPIO_Mode = GPIO_Mode_AF;//
	ledinit_AF2.GPIO_Pin = GPIO_Pin_13;// 
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);// 
	GPIO_Init(GPIOD, &ledinit_AF2);//
	
	
	//IN3 --> PD14--------------------------
	GPIO_InitTypeDef ledinit_AF3;//
	GPIO_StructInit(&ledinit_AF2);// 
	ledinit_AF3.GPIO_Mode = GPIO_Mode_AF;//
	ledinit_AF3.GPIO_Pin = GPIO_Pin_14;// 
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);// 
	GPIO_Init(GPIOD, &ledinit_AF3);//
		
}





// TIM1_CH1 - PE9
//TIM1_CH1N - PE8
//TIM1_CH2 - PE11
//TIM1_CH2N -  PE10
//TIM1_CH3 - PE13
//TIM1_CH3N  - PE12

void BLDC_PWMTimerInit(void) {
	
		
		
		
GPIO_InitTypeDef GPIO_InitStructure;
 TIM_TimeBaseInitTypeDef TIM_BaseStruct;
 TIM_OCInitTypeDef TIM_OCStruct;
 TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
		
		// Clock configuration
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
 

//CH1
	// GPIO Configuration
 GPIO_PinAFConfig(GPIOE, GPIO_PinSource8, GPIO_AF_TIM1);
 GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_TIM1);
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 |GPIO_Pin_10 |GPIO_Pin_11 |GPIO_Pin_12 |GPIO_Pin_13 ;
 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
 GPIO_Init(GPIOE, &GPIO_InitStructure);

// Timer 1 Configuration PWM Channels
 TIM_BaseStruct.TIM_Period = PWM_period-1;
 TIM_BaseStruct.TIM_Prescaler = 4-1; // ---> 42 MHz 
 TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
 TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
 TIM_TimeBaseInit(TIM1, &TIM_BaseStruct);
 TIM_Cmd(TIM1, ENABLE);

// PWM_ Configuration
 TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM1;
 TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_Low;//TIM_OCPolarity_High;
 TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
 TIM_OCStruct.TIM_OutputNState = TIM_OutputNState_Enable;
 TIM_OCStruct.TIM_OCNPolarity = TIM_OCPolarity_Low;//TIM_OCNPolarity_High; 
 TIM_OCStruct.TIM_Pulse = 0;

TIM_OC1Init(TIM1, &TIM_OCStruct);
 TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
 
 
 
 /*Инвертирование каналов для платы Федора, полярность Low*/
 #define CC1NP_LOW (0x1)<<3
 #define CC1P_LOW (0x1)<<1
 #define CC2NP_LOW (0x1)<<7
 #define CC2P_LOW (0x1)<<5
 #define CC3NP_LOW (0x1)<<11
 #define CC3P_LOW (0x1)<<9
 TIM1->CCER = CC1NP_LOW|CC1P_LOW|CC2NP_LOW|CC2P_LOW|CC3NP_LOW|CC3P_LOW;
 
 
 TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
 TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
 TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
 TIM_BDTRInitStructure.TIM_DeadTime = 168; // 1 microsec(168)
 TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;
 TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_Low;
 TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;

TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);
 
 TIM_SelectOCxM(TIM1, TIM_Channel_1, TIM_OCMode_PWM1);
 TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Enable);
 TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Enable);
 
 TIM_SelectOCxM(TIM1, TIM_Channel_2, TIM_OCMode_PWM1);
 TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Enable);
 TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Enable);
 
 TIM_SelectOCxM(TIM1, TIM_Channel_3, TIM_OCMode_PWM1);
 TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Enable);
 TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Enable);
 
 TIM_CtrlPWMOutputs(TIM1, ENABLE);
 
 

}


void TIM2_ini(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_TimeBaseInitTypeDef timer2_init;
	TIM_TimeBaseStructInit(&timer2_init);
	timer2_init.TIM_Period = 4200-1;// ---> 100 microsec
	timer2_init.TIM_Prescaler = 2-1; // ---> 42 MHz
	TIM_TimeBaseInit(TIM2, &timer2_init);
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	
		NVIC_InitTypeDef NVIC_InitStructure;

NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);
	
	
	
	TIM_Cmd(TIM2, ENABLE);
}




void TIM7_ini(void) // TIM for FOC control loop
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	
	TIM_TimeBaseInitTypeDef timer7_init;
	TIM_TimeBaseStructInit(&timer7_init);
	timer7_init.TIM_Period = 4200-1;// ---> 10kHz
	timer7_init.TIM_Prescaler = 2-1; // ---> 42 MHz
	TIM_TimeBaseInit(TIM7, &timer7_init);
	
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);

	
		NVIC_InitTypeDef NVIC_InitStructure;

NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);
	
	
	
	TIM_Cmd(TIM7, ENABLE);
}