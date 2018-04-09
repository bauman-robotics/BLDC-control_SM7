#include "as5048a.h" 
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_exti.h"


void PWM_IN(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef gpio_cfg;
  GPIO_StructInit(&gpio_cfg);
 
	gpio_cfg.GPIO_Pin = GPIO_Pin_0;
  gpio_cfg.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //??????
	//gpio_cfg.GPIO_OType = GPIO_OType_PP;
	//gpio_cfg.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio_cfg.GPIO_Speed = GPIO_Speed_2MHz;
	//GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_TIM2);
	GPIO_Init(GPIOA, &gpio_cfg);
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//base settings
	TIM_TimeBaseInitTypeDef TIM2_Base;
	TIM2_Base.TIM_Period = 0xFFFF;
  TIM2_Base.TIM_Prescaler = 0x0002;
  TIM2_Base.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM2_Base.TIM_CounterMode = TIM_CounterMode_Up;
  TIM2_Base.TIM_RepetitionCounter = 0x0000;
	TIM_TimeBaseInit(TIM2, &TIM2_Base);
	
	//TIM Input Capture Init structure definition 	
	TIM_ICInitTypeDef TIM2_IC;
	TIM2_IC.TIM_Channel = TIM_Channel_1 ; //PA0
	TIM2_IC.TIM_ICFilter = 0x0F; 
	TIM2_IC.TIM_ICPolarity = TIM_ICPolarity_Rising;  // channel_1 captures PWM with rising edge 
	TIM2_IC.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM2_IC.TIM_ICSelection = TIM_ICSelection_DirectTI; //

	
	TIM_PWMIConfig(TIM2, &TIM2_IC);// look to definition and at the manual
	
  TIM_SelectInputTrigger(TIM2, TIM_TS_TI1FP1); // look at the manual
	TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Reset);
	//TIM_SelectMasterSlaveMode(TIM2, TIM_MasterSlaveMode_Enable);
	
	
	
	TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);
	TIM_ITConfig(TIM2, TIM_IT_CC2, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
	NVIC_EnableIRQ(TIM2_IRQn);
	
	
	
}