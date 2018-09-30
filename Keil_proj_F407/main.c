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



#define MOTOR_ENABLE
#define AS5048a_ENABLE
	
float angle, angle_error, angle_test;
float des_val=240,des_val1;
uint32_t t1, t2, t3, t4, dt1, dt22, p, tt1, tt2, dtt, ttt1, ttt2, dttt;

uint16_t ii;

uint32_t cnta;

float voltage, current;

uint16_t angle_raw_16;



float input_m[17] = {3,4,1,2,5,7,6,4,5,7,3,4,8,5,1,9,5};
float buf_raw_m[5];
float buf_sorted_m[5];
uint16_t counter_m;
uint16_t* cm;
uint8_t filled_flag;
float out_med;
uint8_t data_ready;



uint32_t t_uart;
char send_uart;

char str[7];
char send_data[10];
	uint8_t len;

	
	

float sine_desval[SINE_STEPS];

	
	uint16_t angle_counter;
	uint8_t FOC_GO;

//uint16_t angle_record [SAMPLES];

int N_;

uint16_t data1, data2, data3;



float Kp=0.3, Kd, Ki=0.0;

uint8_t calibrate_flag, set_sine_freq_flag;


CQ_average_filter_typedef AngleFilter;

uint16_t freq;


uint16_t receive_test;
//uart test interrupt cycles count
uint32_t uart_cnt;
uint8_t uart_data_ready;// 
uint8_t receive_buffer[9]; // 
uint8_t res_buf_cnt; // 



Osc_qt_TypeDef Osc_struct_qt;

uint8_t sys_mode = 0x1;


int main(void)
	
    {
	 	
	
	Osc_struct_qt.samples = OSC_SAPMLES;
	Osc_struct_qt.prescaler = OSC_PRESCALER;

	
	SPI3_ini();
	
	

	
	TIM5_ini(); // Delay timer   
	
	led15_ini();
	
	
	
	





#ifdef MOTOR_ENABLE

	BLDC_PWMTimerInit(); // init PWM timer
	
	
	TIM4_ini(); // PWM LED Visualisation timer
	
	PWM_ENx_ini();// PWM LED Visualisation


	FOC_InitPosition(&AngleFilter);
	
		
		

	
		fill_sine(sine_desval, SINE_STEPS);
		TIM2_ini(); // Timer for setting desired sine point
	
	
	 TIM7_ini(); // FOC start
	
#endif	

USART_2_init();



	
	while(1)
	{
	
		
		if(uart_data_ready)
	{
		uart_data_ready=0;
		
	
			switch (receive_buffer[0])
			{
				
				
				case 'a': // режим
					if(receive_buffer[1] == 0x00) 
					{
						sys_mode = DISABLED_MODE;
						TIM1->CCR1 = 0;
						TIM1->CCR2 = 0;
						TIM1->CCR3 = 0;
					}
					if(receive_buffer[1] == 0x01) sys_mode = SINE_MODE;
					if(receive_buffer[1] == 0x02) sys_mode = STATIC_MODE;
				break;
				
				
				case 'b':
					calibrate_flag = 1;
			  break;
				
				case 'd': // задаение угла
					
					des_val = (int16_t)(receive_buffer[1]|(receive_buffer[2]<<8));
				
				case 'f': // команда на запись осцилограммы
					Osc_struct_qt.enable = 1;
				break;
				
								
			}
		}
	
		
		
		if(calibrate_flag)
		{
			__disable_irq();
			calibrate_flag=0;
			FOC_InitPosition(&AngleFilter);
			__enable_irq();
			
			

		}
		
		if(set_sine_freq_flag)
		{
			set_sine_freq_flag=0;
			TIM2->ARR= freq;
			TIM2->CNT = 0;
		}
		
		
		
		if(Osc_struct_qt.enable)
		{
			int16_t angle_int16 = (int16_t)(angle*100);
			qt_get_oscillogram(&Osc_struct_qt, &angle_int16);						
		}

	
		//angle = get_angle();
	
	
	}
}















	
	void TIM2_IRQHandler(void)
 {
	 if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {		
			
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		 
		 
		 if(sys_mode==SINE_MODE)
		 {
		 des_val = sine_desval[angle_counter];
		 }
		
		 angle_counter++;
		 if(angle_counter > (SINE_STEPS-1)) angle_counter=0;
		 
		 ttt1 = TIM5->CNT;
		 dttt = ttt1 - ttt2;
		 ttt2 = ttt1;
		 	 
	 }
		
 }
 
 
 
 
 
 void TIM7_IRQHandler(void)
 {
	 if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET) {		
			
			TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
		 
		
		 
		 
		 if(sys_mode != DISABLED_MODE) 
		 {
				angle = CQ_average_angle(&AngleFilter);//CQ_average_angle();//CQ_average_angle();//CQ_IIRF_angle();//CQ_average_angle();//ThirdOrder_average();//average_angle();
				angle_error = des_val - angle;
				FOC(angle, angle_error, Kp, Kd, Ki)	; // Kp, Kd, Ki
		 }
		 
		 
		 
		 tt1 = TIM5->CNT;
		 dtt = tt1 - tt2;
		 tt2 = tt1;
		 
	 }
	
	
 }
 
 
 
 void USART2_IRQHandler()
 {
	 if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)

 {
	 USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	
	uart_cnt++;
	 
	receive_test = USART_ReceiveData(USART2);
		
		
		receive_buffer[res_buf_cnt] = receive_test;
		res_buf_cnt++; 
	 
	 if(res_buf_cnt>2)
			{
				res_buf_cnt=0;
				uart_data_ready = 1;
			} 
	

	}
 }


