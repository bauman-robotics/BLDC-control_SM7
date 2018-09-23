#include "stm32f4xx_adc.h"

#define Pi 3.1415926535897932384
#define OSC_SAPMLES 100
#define OSC_PRESCALER 1

typedef struct
{
	uint8_t enable;
	uint8_t oscillogramms; // Defines oscillograms to record
	uint16_t samples;
	uint8_t prescaler;
	int16_t data_storage[1000];		
	uint16_t osc_cnt;
	uint16_t samp_cnt;
	uint8_t ready;
	uint16_t transmit_cnt;
	uint8_t transmission_finished;
} Osc_qt_TypeDef;



void TIM5_ini(void);
void led15_ini(void);
void myDelay_microsec(uint32_t delay);
void myDelay_ms(uint32_t delay);
void fill_sine(float* sine_arr, float steps);
void USART_2_init(void);
uint8_t qt_get_oscillogram(Osc_qt_TypeDef* Osc_struct, int16_t* Osc_data);

