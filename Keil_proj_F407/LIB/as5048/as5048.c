#include "as5048.h"


#include "mylib.h"

uint16_t ResData1, ResData2, ResData_err;


void SPI3_ini(void)
{
	//PC10 - CLCK
	//PC11 - MISO
	//PC12 - MOSI
	//PC9 - CS
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI3, ENABLE);
	
	GPIO_InitTypeDef SPI3_pins;
	SPI3_pins.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;
	SPI3_pins.GPIO_Mode = GPIO_Mode_AF;
	SPI3_pins.GPIO_Speed = GPIO_Speed_2MHz;
	SPI3_pins.GPIO_OType = GPIO_OType_PP;
	SPI3_pins.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOC, &SPI3_pins);
	
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_SPI3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_SPI3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_SPI3);
	
	GPIO_InitTypeDef SPI3_CS;
	SPI3_CS.GPIO_Pin = GPIO_Pin_9;
	SPI3_CS.GPIO_Mode = GPIO_Mode_OUT;
	SPI3_CS.GPIO_Speed = GPIO_Speed_2MHz;
	SPI3_CS.GPIO_OType = GPIO_OType_PP;
	SPI3_CS.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &SPI3_CS);
	
	CS3_OFF();
	
	
	SPI_InitTypeDef SPI3_encoder;
	SPI3_encoder.SPI_Direction = SPI_Direction_2Lines_FullDuplex ;
	SPI3_encoder.SPI_Mode = SPI_Mode_Master;
	SPI3_encoder.SPI_DataSize = SPI_DataSize_16b; 
	SPI3_encoder.SPI_CPOL = SPI_CPOL_Low;
	SPI3_encoder.SPI_CPHA = SPI_CPHA_2Edge; 
	SPI3_encoder.SPI_NSS = SPI_NSS_Soft;
	SPI3_encoder.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16 ;
	SPI3_encoder.SPI_FirstBit =  SPI_FirstBit_MSB;
	SPI3_encoder.SPI_CRCPolynomial = 7; //??????????????????????????????????????????????????????
	
	SPI_Init(SPI3, &SPI3_encoder);
	SPI_Cmd(SPI3, ENABLE);
	
	SPI_NSSInternalSoftwareConfig(SPI3, SPI_NSSInternalSoft_Set);
}













void encoder_as5048_SPI3(void)
{
	SPI3_ini();
	
	//Delay(500);
	
	
	while(1)
	{
		
	CS3_ON();
	//Delay(5);
	
	
	SPI_I2S_SendData(SPI3, 0xFFFF );
	while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET) {}
	//ResData1 = SPI_I2S_ReceiveData(SPI1);
	//while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
	//Delay(5);
	CS3_OFF();
		
	//Delay(5);
		
	
		
		
		
	CS3_ON();	
	//Delay(5);
	SPI_I2S_SendData(SPI3, 0x0 );
	while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET) {}
	ResData1 = (SPI_I2S_ReceiveData(SPI3)& 0x3FFF)*0.021973997;
	while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET) {}
	//Delay(5);
	CS3_OFF();
		
		
 		
		
		
}
	
	}

	
	
	
	
	
	
	
	// median filter
	float mf_buf[3];
	uint8_t i_m, mf_ready;
		float middle;
	
/*	
float	median(float* mid_buf)
	{
		 if ((mid_buf[0] <= mid_buf[1]) && (mid_buf[0] <= mid_buf[2]))
 {
   middle = (mid_buf[1] <= mid_buf[2]) ? mid_buf[1] : mid_buf[2];
 }
 else if ((mid_buf[1] <= mid_buf[0]) && (mid_buf[1] <= mid_buf[2]))
 {
   middle = (mid_buf[0] <= mid_buf[2]) ? mid_buf[0] : mid_buf[2];
 }
 else
 {
   middle = (mid_buf[0] <= mid_buf[1]) ? mid_buf[0] : mid_buf[1];
 }
 return middle;
	}
	
	*/
	
	float	median(float input)
	{
		if(!mf_ready)
		{
			mf_buf[i_m] = input;
			i_m++;
			middle = input;
			
			if(i_m>=3) 
				{
					
					mf_ready=1;
					i_m=0;
				}
		}
		else
		{
			
			mf_buf[i_m] = input;
			i_m++;
			if(i_m>=3) i_m=0;
				
			
		
		 if ((mf_buf[0] <= mf_buf[1]) && (mf_buf[0] <= mf_buf[2]))
			{
				middle = (mf_buf[1] <= mf_buf[2]) ? mf_buf[1] : mf_buf[2];
			}
		else if ((mf_buf[1] <= mf_buf[0]) && (mf_buf[1] <= mf_buf[2]))
			{
				middle = (mf_buf[0] <= mf_buf[2]) ? mf_buf[0] : mf_buf[2];
			}
		else
			{
				middle = (mf_buf[0] <= mf_buf[1]) ? mf_buf[0] : mf_buf[1];
			}
		return middle;
			
			
			
		}
	}	
	
	
	
	
	
	
	
	
	
	
	extern uint16_t angle_raw_16;
	uint32_t counter_;
 	uint16_t MODF;
	uint8_t pr;
	float angle_return;
		uint8_t  flag_catch;
	float angle_return, fv;
	
	
	float get_angle(void) // with SPI3
	{
		
	myDelay_microsec(1);



	
		if(!pr)
		{		
			CS3_ON();
			myDelay_microsec(1);		
			SPI_I2S_SendData(SPI3, 0xFFFF );
			while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET) {} 
			while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET) {} 
			ResData1 = SPI_I2S_ReceiveData(SPI3);
			myDelay_microsec(1);
			CS3_OFF();		
			myDelay_microsec(1);	
			pr=1;
		}
		
	CS3_ON();	
	myDelay_microsec(1);
	SPI_I2S_SendData(SPI3, 0xFFFF );
	while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET) {}
	while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET) {}
	ResData2 = SPI_I2S_ReceiveData(SPI3);
	myDelay_microsec(1);
	CS3_OFF();
			
			
			
			// if error occurs
	/*		if(ResData2 & 0x4000)
			{
				myDelay_microsec(1);
				CS3_ON();
				myDelay_microsec(1);
				SPI_I2S_SendData(SPI3, 0x4001 );
				while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET) {} 
				while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET) {}
				ResData1 = SPI_I2S_ReceiveData(SPI3);
				myDelay_microsec(1);
				CS3_OFF();
					
				myDelay_microsec(1);	
				CS3_ON();
				myDelay_microsec(5);
				SPI_I2S_SendData(SPI3, 0xFFFF );
				while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET) {} 
				while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET) {}
				ResData_err = SPI_I2S_ReceiveData(SPI3);
				myDelay_microsec(5);
				CS3_OFF();
			}
			*/
			
		
	//angle = (float)(ResData2 & 0x3FFF)*0.021973997;

		angle_raw_16 = ResData2 & 0x3FFF;

		angle_return = (float)(angle_raw_16);
		
		
		
		angle_return = angle_return*0.021973997;
		
		
		
		
		if(angle_return>150)
		{
			flag_catch = 1;
		}

		angle_return = median(angle_return); // median filter
		
		
		if(flag_catch)
		{
			fv = angle_return;
			flag_catch=0;
			
		}
		
		
		
	return 	angle_return;//(float)(ResData2 & 0x3FFF)*0.021973997;	
			
			
	}
	
	
	float get_angle_once(void) // with SPI3
	{
		
	myDelay_microsec(2);



	
			
			CS3_ON();
			myDelay_microsec(1);		
			SPI_I2S_SendData(SPI3, 0xFFFF );
			while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET) {} 
			while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET) {} 
			ResData1 = SPI_I2S_ReceiveData(SPI3);
			myDelay_microsec(1);
			CS3_OFF();		
			myDelay_microsec(1);	
				
		
	CS3_ON();	
	myDelay_microsec(1);
	SPI_I2S_SendData(SPI3, 0x0 );
	while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET) {}
	while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET) {}
	ResData2 = SPI_I2S_ReceiveData(SPI3);
	myDelay_microsec(1);
	CS3_OFF();
			
			
			
			// if error occurs
			if(ResData2 & 0x4000)
			{
				myDelay_microsec(1);
				CS3_ON();
				myDelay_microsec(1);
				SPI_I2S_SendData(SPI3, 0x4001 );
				while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET) {} 
				while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET) {}
				ResData1 = SPI_I2S_ReceiveData(SPI3);
				myDelay_microsec(1);
				CS3_OFF();
					
				myDelay_microsec(1);	
				CS3_ON();
				myDelay_microsec(5);
				SPI_I2S_SendData(SPI3, 0xFFFF );
				while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET) {} 
				while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET) {}
				ResData_err = SPI_I2S_ReceiveData(SPI3);
				myDelay_microsec(5);
				CS3_OFF();
			}
			
			
		
	//angle = (float)(ResData2 & 0x3FFF)*0.021973997;	
			
	return 	(float)(ResData2 & 0x3FFF)*0.021973997;	
			
			
	}
	
	
	
	
	
	
	

	
	
	uint8_t filled;
	float data, position;
	float arr[window], sum, X_i, a_i; // variables for first order moving average
	uint16_t k; // counter
	
	float average_angle(void)
	{
		
		/*
		position = 0;
		for (uint16_t i=0; i<average; i++)
			{
				data = get_angle(); //reading,computing sensor output
				position += data;
			}
					return (position / average);
		*/
		
		
		
		//1) filter initialization 		
		//   Fill the massive and get the sum
		
		if(!filled)
		{
			sum = 0;
			for (int i=0; i < window; i++ )
			 {
				arr[i] = get_angle();
				sum = sum + arr[i];
			 }
			 		 
			 X_i  = sum / window ; // out of the filter
			 filled = 1;
			 k=0;
			 return X_i;
			 
		}
		
		// 2) start filtering
		
		else
		{
			a_i = get_angle();
			sum = sum - arr[k] + a_i;
			X_i  = sum / window ; // out of the filter
			arr[k] = a_i; // substitute thrown out value with new value for cycling
			k++;
			if(k >= window) k=0; // array loop
			return X_i;
			
		}
		

		
		
		
		
		
	}
	
	
	
	
	
	
	
	
	
	
	
	uint8_t filled_second;
	float arr_second[window], sum_second, X_i_second, a_i_second; // variables for first order moving average
	uint16_t k_second; // counter 
		
	float SecondOrder_average(void)
	{
	//	X1 = average_angle(); // firs order output
		
		
		
		
		// second order:
		
		if(!filled_second)
		{
			sum_second = 0;
			for (int i=0; i < window; i++ )
			 {
				arr_second[i] = average_angle(); // accumulating the massive of 1st order output
				sum_second = sum_second + arr_second[i];
			 }
			 		 
			 X_i_second  = sum_second / window ; // out of the filter
			 filled_second = 1;
			 k_second=0;
			 return X_i_second;
			 
		}
		
		// 2) start filtering
		
		else
		{
			a_i_second = average_angle();
			sum_second = sum_second - arr_second[k_second] + a_i_second;
			X_i_second  = sum_second / window ; // out of the filter
			arr_second[k_second] = a_i_second; // substitute thrown out value with new value for cycling
			k_second++;
			if(k_second >= window) k_second=0; // array loop
			return X_i_second;
			
		}
		
		
	}
	
	
	
	
	
	
	
	uint8_t filled_third;
	float arr_third[window], sum_third, X_i_third, a_i_third; // variables for first order moving average
	uint16_t k_third; // counter 
		
	float ThirdOrder_average(void)
	{
	//	X1 = average_angle(); // firs order output
		
		
		
		
		// second order:
		
		if(!filled_third)
		{
			sum_third = 0;
			for (int i=0; i < window; i++ )
			 {
				arr_third[i] = SecondOrder_average(); // accumulating the massive of 1st order output
				sum_third = sum_third + arr_third[i];
			 }
			 		 
			 X_i_third  = sum_third / window ; // out of the filter
			 filled_third = 1;
			 k_second=0;
			 return X_i_third;
			 
		}
		
		// 2) start filtering
		
		else
		{
			a_i_third = SecondOrder_average();
			sum_third = sum_third - arr_third[k_third] + a_i_third;
			X_i_third  = sum_third / window ; // out of the filter
			arr_third[k_third] = a_i_third; // substitute thrown out value with new value for cycling
			k_third++;
			if(k_third >= window) k_third=0; // array loop
			return X_i_third;
			
		}
		
		
	}
	
	
	
	
	////Mean of circular quantities
	float sine_sum, cos_sum, arr_CQ[window], sine_arr[window], cos_arr[window], sine_av, cos_av, X_i_CQ;
	float a_i_CQ, sine_i, cos_i, raw_value;
	uint8_t filled_CQ;
	uint16_t k_CQ;
	
	
	float CQ_average_angle(void)
	{
		if(!filled_CQ)
		{
			sine_sum = 0;
			cos_sum = 0;
			for (int i=0; i < window; i++ )
			 {
				arr_CQ[i] = get_angle()*0.01745329251994329576923690768489 ;//Pi/180; // translating into radians;
				sine_arr[i] = arm_sin_f32(arr_CQ[i]); 
				cos_arr[i] = arm_cos_f32(arr_CQ[i]);
				sine_sum = sine_sum + sine_arr[i];
				cos_sum = cos_sum + cos_arr[i];
			 }
			 
			 sine_av = sine_sum/window;
			 cos_av = cos_sum/window;
			 X_i_CQ  = atan2(sine_av, cos_av)*57.295779513082320876798154814105 ; // out of the filter
			 
			 filled_CQ = 1;
			 k_CQ=0;
			 return X_i_CQ;
			 
		}
		
		// 2) start filtering
		
		else
		{
			raw_value = get_angle();
			a_i_CQ = raw_value*0.01745329251994329576923690768489 ;//Pi/180; // translating into radians;
			sine_i = arm_sin_f32(a_i_CQ);
			cos_i = arm_cos_f32(a_i_CQ);
			sine_sum = sine_sum - sine_arr[k_CQ] + sine_i;
			cos_sum = cos_sum - cos_arr[k_CQ] + cos_i;
			sine_av = sine_sum/window;
			cos_av = cos_sum/window;
			X_i_CQ  = atan2(sine_av, cos_av)*57.295779513082320876798154814105 ;
			
			sine_arr[k_CQ] = sine_i;
			cos_arr[k_CQ] = cos_i;
			 // substitute thrown out value with new value for cycling
			k_CQ++;
			if(k_CQ >= window) k_CQ=0; // array loop
			return X_i_CQ;
			
		}
		
	}
	
	
	
	
	
	
	
	/*
	
	uint8_t filled_ADC;
	uint16_t i_ADC; // counter for filling in
	float data_ADC;
	float arr_ADC[window],  angle_average, a_i_ADC,  des_val_raw; // variables for first order moving average
	uint16_t k_ADC; // counter
	uint32_t ADC_average;
	uint8_t flag_ADC;
  uint32_t sum_ADC;
	
	float ADC_average(void)
	{
		
	
		
		
		
		//1) filter initialization 		
		//   Fill the massive and get the sum
		
		if(!filled_ADC)
		{
			sum_ADC = 0;
			for (int i_ADC=0; i_ADC < window_ADC; i_ADC++ )
			 {
				arr_ADC[i_ADC] = ADC_GetConversionValue(ADC1) ;
				ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_480Cycles);
				ADC_SoftwareStartConv(ADC1);				 
				sum_ADC = sum_ADC + arr_ADC[i_ADC];
			 }
			 		 
			 ADC_average  = sum_ADC / window_ADC ; // out of the filter
			 filled_ADC = 1;
			 k_ADC=0;
			 return ADC_average;
			 
		}
		
		// 2) start filtering
		
		else
		{
			a_i_ADC = get_angle();
			sum_ADC = sum_ADC - arr_ADC[k_ADC] + a_i_ADC;
			ADC_average  = sum_ADC / window_ADC ; // out of the filter
			arr_ADC[k_ADC] = a_i_ADC; // substitute thrown out value with new value for cycling
			k_ADC++;
			if(k_ADC >= window_ADC) k_ADC=0; // array loop
			return ADC_average;
			
		}
		

		
		
		
		
		
	}
	
	*/
	IIR_filter_typedef fsine1;
			IIR_filter_typedef fsine2;
			IIR_filter_typedef fsine3;
			
			
			IIR_filter_typedef fcos1;
			IIR_filter_typedef fcos2;
			IIR_filter_typedef fcos3;
			
	
	uint8_t CQ_IIRF;
	
	float CQ_IIRF_angle(void) // Circular quantities IIR filtered angle
	{
		
		
		
		if(!CQ_IIRF)
		{
			
			
	fsine1.b[0]= 0.024016801444274666     ; fsine1.b[1]=-0.047202999722052032     ; fsine1.b[2]=  0.024016801444274666     ;
	fsine1.a[0]=1 ; fsine1.a[1]=-1.9449352224683314       ; fsine1.a[2]= 0.94576582563482858      ;
			
	fsine2.b[0]= 0.94576582563482858       ; fsine2.b[1]=-0.44715825182338509      ; fsine2.b[2]= 0.22385929993807971       ;
	fsine2.a[0]=1 ; fsine2.a[1]=-1.9880721258078364        ; fsine2.a[2]= 0.98871702484529134       ;		
	
	fsine3.b[0]=  0.17858124414512755       ; fsine3.b[1]=-0.35632880552578683      ; fsine3.b[2]= 0.1785812441451276         ;
	fsine3.a[0]=1 ; fsine3.a[1]=-1.9646507902449557        ; fsine3.a[2]=  0.96537517109617399        ;







	/*		
	fcos1.b[0]=0.0033189100679041354     ; fcos1.b[1]=0.0033189100679041354     ; fcos1.b[2]=0;
	fcos1.a[0]=1 ; fcos1.a[1]=-0.99336217986419173      ; fcos1.a[2]= 0   ;
			
	fcos2.b[0]=  0.12750785034731185       ; fcos2.b[1]=-0.25498606399791035       ; fcos2.b[2]=  0.12750785034731191       	 ;
	fcos2.a[0]=1 ; fcos2.a[1]=-1.9965123169165897       ; fcos2.a[2]= 0.99654949945221294       ;		
	
	fcos3.b[0]= 0.084817749240989254     ; fcos3.b[1]=-0.16958389083412559      ; fcos3.b[2]= 0.084817749240989254      ;
	fcos3.a[0]=1 ; fcos3.a[1]=-1.9899652363002902        ; fcos3.a[2]= 0.99000637067108765          ;				
		*/	
			
			CQ_IIRF=1;
			
		}
		
			raw_value = get_angle();
			a_i_CQ = raw_value*0.01745329251994329576923690768489 ;//Pi/180; // translating into radians;
			sine_i = arm_sin_f32(a_i_CQ);
			cos_i = arm_cos_f32(a_i_CQ);
		
		
		
		//sine
		
		//1
		
	 fsine1.buf_x[2]=fsine1.buf_x[1]; fsine1.buf_x[1]=fsine1.buf_x[0]; fsine1.buf_x[0]= sine_i;
		
	 fsine1.buf_y[0] = fsine1.buf_x[0]*fsine1.b[0]+fsine1.buf_x[1]*fsine1.b[1]+fsine1.buf_x[2]*fsine1.b[2] - fsine1.buf_y[1]*fsine1.a[1] - fsine1.buf_y[2]*fsine1.a[2];
	 fsine1.buf_y[2] =fsine1.buf_y[1]; fsine1.buf_y[1] = fsine1.buf_y[0];
	 
	 //2
	 fsine2.buf_x[2]=fsine2.buf_x[1]; fsine2.buf_x[1]=fsine2.buf_x[0]; fsine2.buf_x[0] = fsine1.buf_y[0];
	 fsine2.buf_y[0] = fsine2.buf_x[0]*fsine2.b[0]+fsine2.buf_x[1]*fsine2.b[1]+fsine2.buf_x[2]*fsine2.b[2] - fsine2.buf_y[1]*fsine2.a[1] - fsine2.buf_y[2]*fsine2.a[2];
	 fsine2.buf_y[2] = fsine2.buf_y[1]; fsine2.buf_y[1] = fsine2.buf_y[0];
	 
	 //3
	 fsine3.buf_x[2]=fsine3.buf_x[1]; fsine3.buf_x[1]=fsine3.buf_x[0]; fsine3.buf_x[0] = fsine2.buf_y[0];
	 fsine3.buf_y[0] = fsine3.buf_x[0]*fsine3.b[0]+fsine3.buf_x[1]*fsine3.b[1]+fsine3.buf_x[2]*fsine3.b[2] - fsine3.buf_y[1]*fsine3.a[1] - fsine3.buf_y[2]*fsine3.a[2];
	 fsine3.buf_y[2] = fsine3.buf_y[1]; fsine3.buf_y[1] = fsine3.buf_y[0];
	 
	 /*
	 //4
	 fsine4.buf_x[2]=fsine4.buf_x[1]; fsine4.buf_x[1]=fsine4.buf_x[0]; fsine4.buf_x[0] = fsine3.buf_y[0];
	 fsine4.buf_y[0] = fsine4.buf_x[0]*fsine4.b[0]+fsine4.buf_x[1]*fsine4.b[1]+fsine4.buf_x[2]*fsine4.b[2] - fsine4.buf_y[1]*fsine4.a[1] - fsine4.buf_y[2]*fsine4.a[2];
	 fsine4.buf_y[2] = fsine4.buf_y[1]; fsine4.buf_y[1] = fsine4.buf_y[0];
	 
	 
	 //5	 
	 fsine5.buf_x[2]=fsine4.buf_x[1]; fsine4.buf_x[1]=fsine4.buf_x[0]; fsine4.buf_x[0] = fsine3.buf_y[0];
	 fsine4.buf_y[0] = fsine4.buf_x[0]*fsine4.b[0]+fsine4.buf_x[1]*fsine4.b[1]+fsine4.buf_x[2]*fsine4.b[2] - fsine4.buf_y[1]*fsine4.a[1] - fsine4.buf_y[2]*fsine4.a[2];
	 fsine4.buf_y[2] = fsine4.buf_y[1]; fsine4.buf_y[1] = fsine4.buf_y[0];
	 */
	 
	 
	 
	 
	 
	  fcos1.buf_x[2]=fcos1.buf_x[1]; fcos1.buf_x[1]=fcos1.buf_x[0]; fcos1.buf_x[0]= cos_i;
	 fcos1.buf_y[0] = fcos1.buf_x[0]*fsine1.b[0]+fcos1.buf_x[1]*fsine1.b[1]+fcos1.buf_x[2]*fsine1.b[2] - fcos1.buf_y[1]*fsine1.a[1] - fcos1.buf_y[2]*fsine1.a[2];
	 fcos1.buf_y[2] =fcos1.buf_y[1]; fcos1.buf_y[1] = fcos1.buf_y[0];
	 
	 
	 fcos2.buf_x[2]=fcos2.buf_x[1]; fcos2.buf_x[1]=fcos2.buf_x[0]; fcos2.buf_x[0] = fcos1.buf_y[0];
	 fcos2.buf_y[0] = fcos2.buf_x[0]*fsine2.b[0]+fcos2.buf_x[1]*fsine2.b[1]+fcos2.buf_x[2]*fsine2.b[2] - fcos2.buf_y[1]*fsine2.a[1] - fcos2.buf_y[2]*fsine2.a[2];
	 fcos2.buf_y[2] = fcos2.buf_y[1]; fcos2.buf_y[1] = fcos2.buf_y[0];
	 
	 
	 fcos3.buf_x[2]=fcos3.buf_x[1]; fcos3.buf_x[1]=fcos3.buf_x[0]; fcos3.buf_x[0] = fcos2.buf_y[0];
	 fcos3.buf_y[0] = fcos3.buf_x[0]*fsine3.b[0]+fcos3.buf_x[1]*fsine3.b[1]+fcos3.buf_x[2]*fsine3.b[2] - fcos3.buf_y[1]*fsine3.a[1] - fcos3.buf_y[2]*fsine3.a[2];
	 fcos3.buf_y[2] = fcos3.buf_y[1]; fcos3.buf_y[1] = fcos3.buf_y[0];
	 
	 
	 
	 
	 /*
	 fcos1.buf_x[2]=fcos1.buf_x[1]; fcos1.buf_x[1]=fcos1.buf_x[0]; fcos1.buf_x[0]= cos_i;
	 fcos1.buf_y[0] = fcos1.buf_x[0]*fcos1.b[0]+fcos1.buf_x[1]*fcos1.b[1]+fcos1.buf_x[2]*fcos1.b[2] - fcos1.buf_y[1]*fcos1.a[1] - fcos1.buf_y[2]*fcos1.a[2];
	 fcos1.buf_y[2] =fcos1.buf_y[1]; fcos1.buf_y[1] = fcos1.buf_y[0];
	 
	 
	 fcos2.buf_x[2]=fcos2.buf_x[1]; fcos2.buf_x[1]=fcos2.buf_x[0]; fcos2.buf_x[0] = fcos1.buf_y[0];
	 fcos2.buf_y[0] = fcos2.buf_x[0]*fcos2.b[0]+fcos2.buf_x[1]*fcos2.b[1]+fcos2.buf_x[2]*fcos2.b[2] - fcos2.buf_y[1]*fcos2.a[1] - fcos2.buf_y[2]*fcos2.a[2];
	 fcos2.buf_y[2] = fcos2.buf_y[1]; fcos2.buf_y[1] = fcos2.buf_y[0];
	 
	 
	 fcos3.buf_x[2]=fcos3.buf_x[1]; fcos3.buf_x[1]=fcos3.buf_x[0]; fcos3.buf_x[0] = fcos2.buf_y[0];
	 fcos3.buf_y[0] = fcos3.buf_x[0]*fcos3.b[0]+fcos3.buf_x[1]*fcos3.b[1]+fcos3.buf_x[2]*fcos3.b[2] - fcos3.buf_y[1]*fcos3.a[1] - fcos3.buf_y[2]*fcos3.a[2];
	 fcos3.buf_y[2] = fcos3.buf_y[1]; fcos3.buf_y[1] = fcos3.buf_y[0];
		*/
		
		X_i_CQ  = atan2(fsine3.buf_y[0], fcos3.buf_y[0])*57.295779513082320876798154814105 ;
		return (float)X_i_CQ;
			
			//sine_sum = sine_sum - sine_arr[k_CQ] + sine_i;
			//cos_sum = cos_sum - cos_arr[k_CQ] + cos_i;
			//sine_av = sine_sum/window;
			//cos_av = cos_sum/window;
			//X_i_CQ  = atan2(sine_av, cos_av)*57.295779513082320876798154814105 ;
			
			//sine_arr[k_CQ] = sine_i;
			//cos_arr[k_CQ] = cos_i;
			 // substitute thrown out value with new value for cycling
			//k_CQ++;
			//if(k_CQ >= window) k_CQ=0; // array loop
			//return X_i_CQ;
			
		}
		
	