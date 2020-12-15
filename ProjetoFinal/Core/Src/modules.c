/*
 * modules.c
 *
 *  Created on: Dec 14, 2020
 *      Author: joaop
 */

#include "main.h"
#include "lcd.h"
#include "core.h"

#define ADC_SCALE (3.3/4095)
#define MAX_DUTY_CYCLE_VALUE 4000
#define DEGREE_CONVERSION 0.005 // 5mV/°C
#define CONVERSION 16

uint32_t adcData[16];
float adc1, temperature1;
float adc2, temperature2;
uint32_t dutyCycle = 0, flag = 0;

void add_water(int time, int type){ // Type 0 - Natural, Type 1 - Quente, Type 2 = Gelada
	if(type == 0)HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	else if (type == 1) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
	else if (type == 2) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
	LCD_String_xy(2,2,"Adic. água...");
	while(dutyCycle < 200){ // 0.2 ms para rampa de subida
		TIM2->CCR1 = dutyCycle*20;
		dutyCycle +=1;
		HAL_Delay(1);
	}
	HAL_Delay(time-450); // permanece o tempo necessário com a bomba aberta
	dutyCycle = 250;
	while(dutyCycle>0){ // 0.25 para rampa de descida
		TIM2->CCR1 = dutyCycle * 16;
		dutyCycle -=1;
		HAL_Delay(1);
	}
	TIM2->CCR1 = 0;
	if(type == 0)HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
	else if (type == 1) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
	else if (type == 2) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
}

void add_co2(int time){
	int press_co2=1;
	press_co2 = HAL_GPIO_ReadPin(GPIOC, PRESS_CO2_Pin);
	if(press_co2==0){
		LCD_Clear();
		LCD_String_xy(1,3,"Sem CO2 no");
		LCD_String_xy(2,3,"reservatório");
		while(1){
			HAL_Delay(4000);
			press_co2 = HAL_GPIO_ReadPin(GPIOC, PRESS_CO2_Pin);
			if(press_co2) break;
		}
	}
	LCD_String_xy(2,2,"Adic. CO2...");
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
	HAL_Delay(time);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
}

void heater(float desired_temperature, ADC_HandleTypeDef* hadc1){
	int i, j, kp=40;
	char string_t[4];
	float error;
	LCD_Clear();
	LCD_String_xy(1,2,"Aquecendo...");
	LCD_String_xy(2,1,"Até ");
	LCD_String_xy(2,7,"°C");
	LCD_String_xy(2,10,"T=");
	LCD_String_xy(2,14,"°C");
	sprintf(string_t, "%02d", (int)desired_temperature);
	LCD_String_xy(2,5,string_t);
	while(1){
		adc1=0;
		for(i=0;i<4;i++){
			HAL_ADC_Start_DMA(hadc1, adcData, CONVERSION);// lê temperatura 4x16 vezes em dois canais (32)
			while(flag==0);
			flag=0;
			for(j=0;j<CONVERSION/2;j++){ // Acumula apenas do canal 1 (A3)
				adc1+=adcData[j];
			}
		}
		temperature1 = (adc1/(CONVERSION*2))*ADC_SCALE; // média canal 1 em volts
		temperature1 /= DEGREE_CONVERSION; // converte para graus
		if(temperature1>100) temperature1 = 100;
		if(temperature1<5) temperature1 = 5;
		sprintf(string_t, "%02d", (int)temperature1);
		LCD_String_xy(2,12,string_t);
		// controle
		error = desired_temperature - temperature1;
		if(error<0) break;
		else{
			TIM2->CCR2 = error * kp;
		}
		HAL_Delay(50);
	}
	TIM2->CCR2 = 0;

}

void cooler(float desired_temperature, ADC_HandleTypeDef* hadc1){

	int i, j, kp=100;
	char string_t[4];
	float error;
	LCD_Clear();
	LCD_String_xy(1,2,"Resfriando...");
	LCD_String_xy(2,1,"Até ");
	LCD_String_xy(2,7,"°C");
	LCD_String_xy(2,10,"T=");
	LCD_String_xy(2,14,"°C");
	sprintf(string_t, "%02d", (int)desired_temperature);
	LCD_String_xy(2,5,string_t);
	while(1){
		adc2=0;
		for(i=0;i<4;i++){
			HAL_ADC_Start_DMA(hadc1, adcData, CONVERSION);// lê temperatura 4x16 vezes em dois canais (32)
			while(flag==0);
			flag=0;
			for(j=CONVERSION/2;j<CONVERSION;j++){ // Acumula apenas do canal 1 (A3)
				adc2+=adcData[j];
			}
		}
		temperature2 = (adc2/(CONVERSION*2))*ADC_SCALE; // média canal 1 em volts
		temperature2 /= DEGREE_CONVERSION; // converte para graus
		if(temperature2>50) temperature2 = 50;
		if(temperature2<5) temperature2 = 5;
		sprintf(string_t, "%02d", (int)temperature2);
		LCD_String_xy(2,12,string_t);
		// controle
		error = temperature2 - desired_temperature;
		if(error<0) break;
		else{
			TIM2->CCR3 = error * kp;
		}
		HAL_Delay(50);
	}
	TIM2->CCR3 = 0;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	flag = 1;
}
