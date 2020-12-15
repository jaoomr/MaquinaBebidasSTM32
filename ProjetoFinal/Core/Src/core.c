/*
 * core.c
 *
 *  Created on: Dec 14, 2020
 *      Author: joaop
 */
#include "main.h"
#include "lcd.h"
#include "modules.h"
#include "core.h"

int read_type_of_capsule(int code1, int code2, int code3){

	LCD_Clear();
	if(code1){
		if(!code3 && !code2){	// code 100 - tipo 5 - Refrigerante

			LCD_String_xy(1,2,"Refrigerante");
			LCD_String_xy(2,4,"Confirma?");
			return 5;
		}
		else{
			LCD_String_xy(1,4,"Erro na");
			LCD_String_xy(2,4,"leitura!");
			return 0;
		}
	}
	else{
		LCD_String_xy(2,4,"Confirma?");
		if(code2==1){
			if(code3==1){ // code 011 - Tipo 4 - Chá Quente
				LCD_String_xy(1,2,"Chá quente");
				return 4;
			}
			else{ // code 010 - Tipo 3 - Chá Gelado
				LCD_String_xy(1,2,"Chá gelado");
				return 3;
			}
		}
		else{
			if(code3==1){ // code 001 - Tipo 2 - Agua c/ gás
				LCD_String_xy(1,2,"Agua c/ gás");
				return 2;
			}
			else{ // code 000 - Tipo 1 - Agua
				LCD_String_xy(1,6,"Agua");
				return 1;
			}
		}
	}
}

void preparing(int type, ADC_HandleTypeDef* hadc1){
	LCD_Clear();
	int confirm = 0, add = 0, sub = 0;
	int choice=0; // (0 - Natural, 1 - Quente, 2 - Gelada)
	HAL_Delay(500);
	switch (type){
		case 1:
			LCD_String_xy(1,2,"Escolha: (+/-)");
			LCD_String_xy(2,4,"Natural");
			while(confirm==0){
				confirm = HAL_GPIO_ReadPin(GPIOB, CONFIRM_Pin);
				add = HAL_GPIO_ReadPin(GPIOB, ADD_Pin);
				sub = HAL_GPIO_ReadPin(GPIOB, SUB_Pin);
				HAL_Delay(500);
				if(add || sub){
					if(add){
						choice++;
						if(choice>2){
							choice = 0;
						}
					}
					if(sub){
						choice--;
						if(choice<0){
							choice=2;
						}
					}
					LCD_Clear();
					LCD_String_xy(1,2,"Escolha: (+/-)");
					switch (choice){
						case 0: LCD_String_xy(2,4,"Natural"); break;
						case 1:	LCD_String_xy(2,4,"Quente"); break;
						case 2: LCD_String_xy(2,4,"Gelada"); break;
					}
				}
			}

			LCD_Clear();
			switch (choice){
				case 0:
					LCD_String_xy(1,4,"Natural");
					add_water(3000, 0);
					LCD_Clear();
					break;
				case 1:
					heater(60, hadc1);
					LCD_Clear();
					LCD_String_xy(1,4,"Quente");
					add_water(3000, 1);
					LCD_Clear();
					break;
				case 2:
					HAL_Delay(100);
					cooler(15, hadc1);
					LCD_Clear();
					LCD_String_xy(1,4,"Gelada");
					add_water(3000, 2);
					LCD_Clear();
					break;
			}
			break;
		case 2:
			LCD_String_xy(1,2,"Agua c/ gás");
			cooler(15, hadc1);
			LCD_Clear();
			LCD_String_xy(1,2,"Agua c/ gás");
			add_water(3000, 2);
			LCD_Clear();
			LCD_String_xy(1,2,"Agua c/ gás");
			add_co2(1500);
			LCD_Clear();
			break;
		case 3:
			LCD_String_xy(1,2,"Chá gelado");
			cooler(20, hadc1);
			LCD_Clear();
			LCD_String_xy(1,2,"Chá gelado");
			add_water(2700, 2);
			LCD_Clear();
			break;
		case 4:
			LCD_String_xy(1,2,"Chá quente");
			heater(60, hadc1);
			LCD_Clear();
			LCD_String_xy(1,2,"Chá quente");
			add_water(2700, 1);
			LCD_Clear();
			break;
		case 5:
			LCD_String_xy(1,2,"Refrigerante");
			cooler(17, hadc1);
			LCD_Clear();
			LCD_String_xy(1,2,"Refrigerante");
			add_water(4000, 2);
			LCD_Clear();
			LCD_String_xy(1,2,"Refrigerante");
			add_co2(2560);
			LCD_Clear();
			break;
	}

	LCD_String_xy(2,4,"Pronto!");
	HAL_Delay(3000);
}
