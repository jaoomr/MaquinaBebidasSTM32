/*
 * core.h
 *
 *  Created on: Dec 14, 2020
 *      Author: joaop
 */

#ifndef INC_CORE_H_
#define INC_CORE_H_

#include<stdint.h>
#include<stdio.h>
#include "main.h"
#include "modules.h"
#include "lcd.h"


int read_type_of_capsule(int code1, int code2, int code3);
void preparing(int type, ADC_HandleTypeDef* hadc1);

#endif /* INC_CORE_H_ */
