#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "mylib.h"



void TIM5_ini(void) /// Time measuring timer
{
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
		//base settings
	TIM_TimeBaseInitTypeDef TIM5_Base;
	TIM5_Base.TIM_Period = 0xFFFFFFFF;
  TIM5_Base.TIM_Prescaler = 84-1; // 1MHz
  TIM5_Base.TIM_ClockDivision = TIM_CKD_DIV1 ; //
  TIM5_Base.TIM_CounterMode = TIM_CounterMode_Up;
  TIM5_Base.TIM_RepetitionCounter = 0x0000;
	TIM_TimeBaseInit(TIM5, &TIM5_Base);
	TIM_Cmd(TIM5, ENABLE);
}






void led15_ini(void)
{

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef LED_pin;
	GPIO_StructInit(&LED_pin);
	LED_pin.GPIO_Pin = GPIO_Pin_15;
	LED_pin.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOD, &LED_pin);
}













 //Delay


uint32_t time1;


void myDelay_microsec(uint32_t delay)
{
	time1 = TIM5->CNT;
	while( ((TIM5->CNT) - time1) < delay) {}
}


void myDelay_ms(uint32_t delay)
{
	time1 = TIM5->CNT;
	while( ((TIM5->CNT) - time1) < 1000*delay) {}
	
}
	
























	uint32_t SYSCLK_Frequency_; /*!<  SYSCLK clock frequency expressed in Hz */
  uint32_t HCLK_Frequency_;   /*!<  HCLK clock frequency expressed in Hz   */
  uint32_t PCLK1_Frequency_;  /*!<  PCLK1 clock frequency expressed in Hz  */
  uint32_t PCLK2_Frequency_; 
	
void get_clock(void)
{
		RCC_ClocksTypeDef Clocks;
	RCC_GetClocksFreq(&Clocks) ;
	
	SYSCLK_Frequency_ = Clocks.SYSCLK_Frequency;
	HCLK_Frequency_ = Clocks.HCLK_Frequency;
	PCLK1_Frequency_ = Clocks.PCLK1_Frequency;
	PCLK2_Frequency_ = Clocks.PCLK2_Frequency;
}



void USART_2_init(void) //PD6,PD5
 {
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	 
	GPIO_InitTypeDef USART2_ini;//
	USART2_ini.GPIO_Mode = GPIO_Mode_AF;//
	USART2_ini.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;// 
	USART2_ini.GPIO_Speed = GPIO_Speed_2MHz;
  USART2_ini.GPIO_OType = GPIO_OType_PP;
  USART2_ini.GPIO_PuPd = GPIO_PuPd_UP; 
	GPIO_Init(GPIOD, &USART2_ini);// 
	 
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);// 
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);//
	 
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE) ;
	 
	USART_InitTypeDef USART2_user;
	USART2_user.USART_BaudRate= 115200;
	USART2_user.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	 USART2_user.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	 USART2_user.USART_Parity = USART_Parity_No;
	 USART2_user.USART_StopBits = USART_StopBits_1;
	 USART2_user.USART_WordLength = USART_WordLength_8b;
	 
	 USART_Init(USART2, &USART2_user);
	 
	 /*
	 	NVIC_InitTypeDef NVIC_InitStructure2;

NVIC_InitStructure2.NVIC_IRQChannel = USART2_IRQn;
NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 1;
NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 0;
NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure2);
	 
	 
	 
	 //NVIC_EnableIRQ(USART2_IRQn);
	 USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	 
	 */
	 
	 USART_Cmd(USART2, ENABLE);
 }







