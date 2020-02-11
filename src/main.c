
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
ADC_InitTypeDef ADC_InitStruct;
ADC_CommonInitTypeDef ADC_CommonInitStruct;

uint16_t adc_value;
float adc_voltage;

void GPIO_Config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);

}

void ADC_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);

	ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4;

	ADC_CommonInit(&ADC_CommonInitStruct);


	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;//cozunurlugunu max ayarlad�k ancak bu durum cok da iyi degil ses vs herseyden etkilenir

	ADC_Init(ADC1 ,&ADC_InitStruct);

	ADC_Cmd(ADC1,ENABLE);//cevresel paramerteleri kullandigimizda bu sekilde aktif etmeliyiz

}

uint16_t Read_ADC()
{
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_56Cycles);

	ADC_SoftwareStartConv(ADC1);//ADC yi yazilimsal olarak baslattik //adc okumas� bittiginde EOC bayragi kalkar asagida while ile bu durum olusana kadar bekledik

	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);//adc okumasi bitene kadar beklememiz lazim burada o islemi gerceklestiriyoruz

	return ADC_GetConversionValue(ADC1);//ADC degisim degerlerini okumak icin bu degerleri kulland�k.

}


int main(void)
{
	GPIO_Config();
	ADC_Config();

  while (1)
  {
	  adc_value = Read_ADC();//surekli ADC okumasi yapar.
	  adc_voltage = (0.000805)*adc_value;
  }
}


void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
