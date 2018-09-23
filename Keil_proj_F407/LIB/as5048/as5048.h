#ifndef AS5048_H
#define AS5048_H



#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"
#include "math.h"
#include "arm_math.h"



#define window 100
#define window_ADC 1000
//#define SAMPLES 20000
//#define RECORD_DATA 0


#define CS3_ON() GPIO_ResetBits(GPIOC, GPIO_Pin_9)
#define CS3_OFF() GPIO_SetBits(GPIOC, GPIO_Pin_9)

#define CS1_ON() GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define CS1_OFF() GPIO_SetBits(GPIOA, GPIO_Pin_4)


typedef struct
{
	double buf_x[3];
	double buf_y[3];
	double a[4];
	double b[4];
	
		
}IIR_filter_typedef;


typedef struct
{
	float buf[3]; // buffer
	uint8_t i_m; // counter
	uint8_t ready; // ready flag
	float middle; // result/output
} MedianFilter;






/*
uint8_t filled_ADC;
	uint16_t i_ADC; // counter for filling in
	float data_ADC;
	float arr_ADC[window],  angle_average, a_i_ADC,  des_val_raw; // variables for first order moving average
	uint16_t k_ADC; // counter
	uint32_t ADC_average;
	uint8_t flag_ADC;
  uint32_t sum_ADC;
*/



/*


typedef struct
{
  uint8_t filled;              

  uint16_t i_buf;     // Scounter for buffering
                                     

  uint16_t window_av   //Specifies the speed for the selected pins.
                                       

  uint16_t arr[window_av];   // Specifies the operating output type for the selected pins.
                                       

  GPIOPuPd_TypeDef GPIO_PuPd;     // Specifies the operating Pull-up/Pull down for the selected pins.
                                       
}MovingAveage_TypeDef;

*/


typedef struct{
	
	uint8_t filled_CQ; // flag shows weather the buffer is filled or not
	float sine_sum;
	float cos_sum;	
	float arr_CQ[window];
	float sine_arr[window];
	float cos_arr[window];
	float sine_av;
	float cos_av;
	float X_i_CQ;
	float a_i_CQ;
	float sine_i;
	float cos_i;
	float raw_value;
	uint16_t k_CQ;
	
	
}CQ_average_filter_typedef;




void encoder_as5048_SPI3(void);
void SPI3_ini(void);
float get_angle(void);
float average_angle(void) ;
float get_angle_once(void);
float  SecondOrder_average(void);
float ThirdOrder_average(void);
float CQ_average_angle(CQ_average_filter_typedef* filter);
float CQ_IIRF_angle(void);
float	median(float input, MedianFilter* filter);
float	median_n(float input, uint16_t order, float* buf_raw, float* buf_sorted, uint16_t* counter, uint8_t* filled_flag);
void SPI1_init(void);












#endif
