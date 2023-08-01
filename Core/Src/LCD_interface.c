/*
 * LCD_interface.c
 *
 *  Created on: Mar 19, 2023
 *      Author: El-Wattaneya
 */
#include "LCD_interface.h"
static void Trigger_Enable();
static void Set_Cursor_Pos(u8 row,u8 column);
void LCD_Init(void)
{
	MGPIO_voidSetPinMode(LCD_PORT,D4,GPIO_GP_OUTPUT_PP_2MHZ);
	MGPIO_voidSetPinMode(LCD_PORT,D5,GPIO_GP_OUTPUT_PP_2MHZ);
	MGPIO_voidSetPinMode(LCD_PORT,D6,GPIO_GP_OUTPUT_PP_2MHZ);
	MGPIO_voidSetPinMode(LCD_PORT,D7,GPIO_GP_OUTPUT_PP_2MHZ);
	MGPIO_voidSetPinMode(LCD_PORT,RS,GPIO_GP_OUTPUT_PP_2MHZ);
	MGPIO_voidSetPinMode(LCD_PORT,RW,GPIO_GP_OUTPUT_PP_2MHZ);
	MGPIO_voidSetPinMode(LCD_PORT,EN,GPIO_GP_OUTPUT_PP_2MHZ);
	//_delay_ms(20);
	for(u8 i=0;i<10;i++)
	{
		asm("NOP");
	}
	LCD_Send_Command(0x33);
	LCD_Send_Command(0x32);
	LCD_Send_Command(_LCD_4BIT_MODE_2_LINE);
	LCD_Send_Command(_LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
	LCD_Send_Command(_LCD_ENTRY_MODE_INC_SHIFT_OFF);
	LCD_Send_Command(_LCD_DDRAM_START);
	LCD_Send_Command(_LCD_CLEAR);
}
void LCD_Send_Command(u8 command)
{
	MGPIO_voidSetPinValue(LCD_PORT,RS, GPIO_LOW);
	MGPIO_voidSetPinValue(LCD_PORT,RW, GPIO_LOW);


	(GET_BET(command,7)) ? MGPIO_voidSetPinValue(LCD_PORT,D7,GPIO_HIGH) : MGPIO_voidSetPinValue(LCD_PORT,D7,GPIO_LOW);
	(GET_BET(command,6)) ? MGPIO_voidSetPinValue(LCD_PORT,D6,GPIO_HIGH) : MGPIO_voidSetPinValue(LCD_PORT,D6,GPIO_LOW);
	(GET_BET(command,5)) ? MGPIO_voidSetPinValue(LCD_PORT,D5,GPIO_HIGH) : MGPIO_voidSetPinValue(LCD_PORT,D5,GPIO_LOW);
	(GET_BET(command,4)) ? MGPIO_voidSetPinValue(LCD_PORT,D4,GPIO_HIGH) : MGPIO_voidSetPinValue(LCD_PORT,D4,GPIO_LOW);
	//Trigger Enable
	Trigger_Enable();
	(GET_BET(command,3)) ? MGPIO_voidSetPinValue(LCD_PORT,D7,GPIO_HIGH) : MGPIO_voidSetPinValue(LCD_PORT,D7,GPIO_LOW);
	(GET_BET(command,2)) ? MGPIO_voidSetPinValue(LCD_PORT,D6,GPIO_HIGH) : MGPIO_voidSetPinValue(LCD_PORT,D6,GPIO_LOW);
	(GET_BET(command,1)) ? MGPIO_voidSetPinValue(LCD_PORT,D5,GPIO_HIGH) : MGPIO_voidSetPinValue(LCD_PORT,D5,GPIO_LOW);
	(GET_BET(command,0)) ? MGPIO_voidSetPinValue(LCD_PORT,D4,GPIO_HIGH) : MGPIO_voidSetPinValue(LCD_PORT,D4,GPIO_LOW);
	//Trigger Enable
	Trigger_Enable();
}
void LCD_Send_Char(u8 _char)
{
	MGPIO_voidSetPinValue(LCD_PORT,RS, GPIO_HIGH);
	MGPIO_voidSetPinValue(LCD_PORT,RW, GPIO_LOW);


	(GET_BET(_char,7)) ? MGPIO_voidSetPinValue(LCD_PORT,D7,GPIO_HIGH) : MGPIO_voidSetPinValue(LCD_PORT,D7,GPIO_LOW);
	(GET_BET(_char,6)) ? MGPIO_voidSetPinValue(LCD_PORT,D6,GPIO_HIGH) : MGPIO_voidSetPinValue(LCD_PORT,D6,GPIO_LOW);
	(GET_BET(_char,5)) ? MGPIO_voidSetPinValue(LCD_PORT,D5,GPIO_HIGH) : MGPIO_voidSetPinValue(LCD_PORT,D5,GPIO_LOW);
	(GET_BET(_char,4)) ? MGPIO_voidSetPinValue(LCD_PORT,D4,GPIO_HIGH) : MGPIO_voidSetPinValue(LCD_PORT,D4,GPIO_LOW);
	//Trigger Enable
	Trigger_Enable();
	(GET_BET(_char,3)) ? MGPIO_voidSetPinValue(LCD_PORT,D7,GPIO_HIGH) : MGPIO_voidSetPinValue(LCD_PORT,D7,GPIO_LOW);
	(GET_BET(_char,2)) ? MGPIO_voidSetPinValue(LCD_PORT,D6,GPIO_HIGH) : MGPIO_voidSetPinValue(LCD_PORT,D6,GPIO_LOW);
	(GET_BET(_char,1)) ? MGPIO_voidSetPinValue(LCD_PORT,D5,GPIO_HIGH) : MGPIO_voidSetPinValue(LCD_PORT,D5,GPIO_LOW);
	(GET_BET(_char,0)) ? MGPIO_voidSetPinValue(LCD_PORT,D4,GPIO_HIGH) : MGPIO_voidSetPinValue(LCD_PORT,D4,GPIO_LOW);
	//Trigger Enable
	Trigger_Enable();
}
void LCD_Send_Char_Pos(u8 _char,u8 row,u8 column)
{
	Set_Cursor_Pos(row,column);
	LCD_Send_Char(_char);
}
void LCD_Send_String(u8 *string)
{
	while(*string !='\0')
	{
		LCD_Send_Char(*string++);
	}
}
void LCD_Send_String_Pos(u8 *string,u8 row,u8 column)
{
	Set_Cursor_Pos(row,column);
	LCD_Send_String(string);
}
void LCD_Send_Number(u32 num)
{
	 u8 arr[10],i=0,j=0;
		   if(num == 0)
		   {
			   LCD_Send_Char('0');
		   }
		   else
		   {
			   while(num)
			   {
					arr[i]=num%10+'0';
					num/=10;
					i++;
			   }
			   for(j=i;j>0;j--)
			   {
				   LCD_Send_Char(arr[j-1]);
			   }
		   }
}
void LCD_Send_Number_Pos(u32 num,u8 row,u8 column)
{
	Set_Cursor_Pos(row,column);
	LCD_Send_Number(num);
}
void LCD_Send_Cust_char(const u8 _char[],u8 row,u8 column,u8 mem_pos)
{
	u8 lcd_counter=0;
	LCD_Send_Command((_LCD_CGRAM_START + (mem_pos*8)));
    for(lcd_counter =0;lcd_counter <= 7;lcd_counter++){
    	LCD_Send_Char(_char[lcd_counter]);
    }
    LCD_Send_Char_Pos(mem_pos,row,column);
}


static void Trigger_Enable()
{
	MGPIO_voidSetPinValue(LCD_PORT,EN,GPIO_HIGH);
	for(u8 i=0;i<10;i++)
	{
		asm("NOP");
	}
	//DELAY
	MGPIO_voidSetPinValue(LCD_PORT,EN,GPIO_LOW);
	for(u16 i=0;i<2000;i++)
	{
		asm("NOP");
	}
}
static void Set_Cursor_Pos(u8 row,u8 column)
{
	column--;
	switch(row)
			{
	            case ROW1: LCD_Send_Command((0x80 + column)); break;
	            case ROW2: LCD_Send_Command((0xc0 + column)); break;
	            default:;
	        }
}
