/*
 * modules.h
 *
 *  Created on: Dec 14, 2020
 *      Author: joaop
 */

#ifndef INC_MODULES_H_
#define INC_MODULES_H_

#include<stdint.h>
#include<stdio.h>
#include "main.h"
#include "lcd.h"

void add_water(int time, int type);
void heater(float desired_temperature, ADC_HandleTypeDef* hadc1);
void cooler(float desired_temperature, ADC_HandleTypeDef* hadc1);
void add_co2(int time);

#endif /* INC_MODULES_H_ */
