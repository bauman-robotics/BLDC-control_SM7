
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "math.h"
#include "stm32f10x_adc.h"


void TIM4_ini(void);
void myDelay_microsec(uint32_t delay);
void myDelay_ms(uint32_t delay);
void FOC(float angle, float error_angle, float K_p, float K_d);
void ADC_initt(void);

# define PolePairs 15
#define Vdc 30
#define window 100