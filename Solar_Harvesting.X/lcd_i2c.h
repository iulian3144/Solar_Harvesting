/*
 * File:   lcd_i2c.h
 * Author: Silviu Chirica
 */

#ifndef _LCD_I2C_H_
#define _LCD_I2C_H_

#include <xc.h> // include processor files - each processor file is guarded.

void I2C_Master_Init(const unsigned long c);
void I2C_Master_Wait();
void I2C_Master_Start();
void I2C_Master_RepeatedStart();
void I2C_Master_Stop();
void I2C_Master_Write(unsigned d);
void I2C_Write_Display(unsigned d);
unsigned short I2C_Master_Read(unsigned short a);

void Lcd_Port(char data);
void Lcd_Cmd(char a);
void Lcd_Clear();
void Lcd_Set_Cursor(char a, char b);
void Lcd_Init();
void Lcd_Write_Char(char a);
void Lcd_Write_String(char *a);
void Lcd_Shift_Right();
void Lcd_Shift_Left();
void Cursor_On();
void Cursor_Off();
void Cursor_Left();
void Cursor_Right();

#endif // _LCD_I2C_H_
