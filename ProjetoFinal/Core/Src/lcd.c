/*
 * lcd.c
 *
 *  Created on: Nov 3, 2020
 *      Author: joaop
 */
#include "main.h"
#include "lcd.h"

unsigned char acomacento[8] = { // Definição dos caracteres especiais (leds que devem ser acesos)
	0b00010,
	0b00100,
	0b01110,
	0b00001,
	0b01111,
	0b10001,
	0b01111,
	0b00000
};

unsigned char acomtil[8] = {
	0b01110,
	0b00000,
	0b01110,
	0b00001,
	0b01111,
	0b10001,
	0b01111,
	0b00000
};

unsigned char cedilha[8] = {
	0b00000,
	0b01111,
	0b10000,
	0b10000,
	0b10000,
	0b01111,
	0b00100,
	0b00100
};

unsigned char ecomacento[8] = {
	0b00010,
	0b00100,
	0b01110,
	0b10001,
	0b11111,
	0b10000,
	0b01111,
	0b00000
};

unsigned char ocomtil[8] = {
	0b01110,
	0b00000,
	0b01110,
	0b10001,
	0b10001,
	0b10001,
	0b01110,
	0b00000
};

unsigned char ocomacento[8] = {
  0b00010,
  0b00100,
  0b01110,
  0b10001,
  0b10001,
  0b10001,
  0b01110,
  0b00000
};

unsigned char grausimbolo[8] = {
  0b01110,
  0b01010,
  0b01110,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};


char aacentuado [2] = "á";
char eacentuado [2] = "é";
char otil [2] = "õ";
char atil [2] = "ã";
char ccedilha [2] = "ç";
char oacentuado [2] = "ó";
char grau [2] = "°";


void writePort(char x){ // Função auxiliar para escrever na porta 8 bits
	int value;
	value = x & 0x01;
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, value);
	value = x & 0x02;
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, value);
	value = x & 0x04;
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, value);
	value = x & 0x08;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, value);
	value = x & 0x10;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, value);
	value = x & 0x20;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, value);
	value = x & 0x40;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, value);
	value = x & 0x80;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, value);
}


void LCD_Init()  // Inicializa
{
	LCD_Custom_Char(0, acomacento);
	LCD_Custom_Char(1, acomtil);
	LCD_Custom_Char(2, ecomacento);
	LCD_Custom_Char(3, ocomtil);
	LCD_Custom_Char(4, cedilha); // Salva desenhos dos caracteres especiais
	LCD_Custom_Char(5, ocomacento);
	LCD_Custom_Char(6, grausimbolo);

	HAL_Delay(15);
    LCD_Command(0x38);
    LCD_Command(0x01);
    LCD_Command(0x0c);
    LCD_Command(0x06);
}

void LCD_Clear() // Limpa o display
{
    	LCD_Command(0x01);
}

void LCD_Command(char cmd) // Envia comandos para o display
{

	writePort(cmd);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 1);
	asm("nop");
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 0);
	HAL_Delay(3);
}

void LCD_Char(char dat) // Escreve um caractere no display
{
	writePort(dat);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 1);
	asm("nop");
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 0);
	HAL_Delay(1);
}

void LCD_String(const char *msg) // Escreve uma string no display
{
	while((*msg)!=0)
	{
	    if((*msg) == aacentuado[0] && *(msg+1) == aacentuado[1]){
	    	LCD_Char(0);
	    	msg+=2;
	    }
	    else if((*msg) == atil[0] && *(msg+1) == atil[1]){
	    	LCD_Char(1);
	    	msg+=2;
	    }
	    else if((*msg) == eacentuado[0] && *(msg+1) == eacentuado[1]){
	    	LCD_Char(2);
	    	msg+=2;
	    }
	    else if((*msg) == otil[0] && *(msg+1) == otil[1]){
	    	LCD_Char(3);
	    	msg+=2;
	    }
	    else if((*msg) == ccedilha[0] && *(msg+1) == ccedilha[1]){
	    	LCD_Char(4);
	    	msg+=2;
	    }
	    else if((*msg) == oacentuado[0] && *(msg+1) == oacentuado[1]){
			LCD_Char(5);
			msg+=2;
	    }
	    else if((*msg) == grau[0] && *(msg+1) == grau[1]){
			LCD_Char(6);
			msg+=2;
	    }
	    else{
		  LCD_Char(*msg);
		  msg++;
	    }
	}
}


void LCD_Custom_Char (unsigned char loc, unsigned char *msg) // Grava caracteres especiais na cgram
{
    unsigned char i;
    if(loc<8)
    {
     LCD_Command (0x40 + (loc*8));
     for(i=0;i<8;i++)
        LCD_Char(msg[i]);
    }
}

void LCD_String_xy(char row,char pos,const char *msg) // Escreve string na posição X Y desejada
{
    char location=0;
    if(row<=1)
    {
        location=(0x80) | ((pos) & 0x0f);
        LCD_Command(location);
    }
    else
    {
        location=(0xC0) | ((pos) & 0x0f);
        LCD_Command(location);
    }
    LCD_String(msg);
}
