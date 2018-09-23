#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "mylib.h"
#include "math.h"



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
	 
	 
	 	NVIC_InitTypeDef NVIC_InitStructure2;

NVIC_InitStructure2.NVIC_IRQChannel = USART2_IRQn;
NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 5;
NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 0;
NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure2);
	 
	 
	 
	 //NVIC_EnableIRQ(USART2_IRQn);
	 USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	 
	 
	 
	 USART_Cmd(USART2, ENABLE);
 }




void fill_sine(float* sine_arr, float steps)
{
		for ( int i =0; i < steps; i++)
			{
		    //sine_arr[i] = sin( ((float)(i/(steps-1)) *2*Pi))*40 + 120;
				sine_arr[i] = sin( ((float)(i/(steps-1)) *2*Pi))*90 ;
			}

}























//-----------Send byte

void UART_send_byte(uint8_t byte)
{
	USART_SendData (USART2, (uint16_t)byte);
	while (!USART_GetFlagStatus(USART2, USART_FLAG_TXE)) {}
}





// send 16 bit value

void UART2_Send_16bValue(uint16_t data, char key)
{
					//Деление на 2 байта и добавление символа '\n'
	uint8_t	Data_L = (uint8_t)(data&0x00FF);
	uint8_t	Data_H = (uint8_t)((data&0xFF00)>>8);
	UART_send_byte((uint8_t)('\n'));
	UART_send_byte((uint8_t)key);
	UART_send_byte(Data_L);
	UART_send_byte(Data_H);
}














void send_finish_sequence(void)
{
	UART_send_byte((uint8_t)('f'));
	UART_send_byte((uint8_t)('i'));
	UART_send_byte((uint8_t)('n'));
	UART_send_byte((uint8_t)('i'));
	UART_send_byte((uint8_t)('s'));
	UART_send_byte((uint8_t)('h'));
	UART_send_byte((uint8_t)('e'));
	UART_send_byte((uint8_t)('d'));
}






















uint8_t qt_get_oscillogram(Osc_qt_TypeDef* Osc_struct, int16_t* Osc_data)
{

		
			if(Osc_struct->osc_cnt< Osc_struct->samples) // если осциллограмма не заполнена - заполнять
			{
                if(Osc_struct->samp_cnt< Osc_struct->prescaler) // выборка значений с заданной частотой
                {
                    Osc_struct->samp_cnt++;
                }
                else
                {
                    Osc_struct->samp_cnt=0;
									
									
											Osc_struct->data_storage[Osc_struct->osc_cnt]	=	*Osc_data;
											Osc_struct->osc_cnt++;
											
								}
									
                    
			        
			}
			else
			{
				Osc_struct->ready = 1; // флаг готовности осциллограммы
				
				//--
				//motor_run=0;
				//motor_mode=COMMON_MODE;
				//MDR_TIMER3->CCR4 = 2000; // остановить мотор
				//--
				
			}
			
			
			if(Osc_struct->ready)
			{
				
					if(	(	Osc_struct->transmit_cnt	<	Osc_struct->samples	)	) // передавать, пока не будет передан весь массив
						{		
			
							UART2_Send_16bValue(Osc_struct->data_storage[Osc_struct->transmit_cnt], 'a');
							
												
							Osc_struct->transmit_cnt++;
			
						}
				else
						{
							Osc_struct->transmission_finished = 1; // осциллограмма передана
						}
				
				
			}
			
			if(Osc_struct->transmission_finished) // по завершении передачи отправить завершающую последовательность
				{
					myDelay_ms(100);//Delay_ms_func(100);
					send_finish_sequence();
					Osc_struct->osc_cnt=0;
					Osc_struct->samp_cnt=0;
					Osc_struct->ready=0;
					Osc_struct->transmit_cnt=0;
					Osc_struct->transmission_finished=0;
					Osc_struct->enable=0;
					
					return 0;
				}
				
	return 1;
        
       
	
}




