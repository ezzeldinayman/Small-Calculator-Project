/*
 * Calculator.c
 *
 * Created: 09-Mar-22 6:30:46 AM
 *  Author: ezz_a
 */ 

#include "math.h"
#include "LCD.h"
#include "keypad.h"
#include "util/delay.h"
#define MAX_DIGITS 4

int operandtoInteger(char *operand, char n);
int charArrayToInt(char *arr, char n);
int calcResult(int x, int y, char op);
void printInt(int z);
int readOperand(char *operand, char n, char *op);

int main(void)
{
	LCD_vInit();
	keypad_vInit();
	LCD_vSend_string("Hello, World");
	_delay_ms(500);
	LCD_clearscreen();
	char *operand1 = 0x800;
	char *operand2 = 0x700;
	//char inp=0xFF;
	int *x = 0x600;
	int *y = 0x604;
	char *op = 0x650;
	char n=0;
	char *f = 0x654;
	char m=0;
	int result;
    while(1)
    {
        //TODO:: Please write your application code 
		label:
		(*x) = readOperand(operand1,n,op);
		
		if(op=='A')
		{
			LCD_clearscreen; 
			goto label;
		}			
		LCD_vSend_char((*op));
		
		(*y)=readOperand(operand2,m,f);
		
		if((*f)=='=')
		{
			LCD_movecursor(2,13);
			result = calcResult((*x),(*y),(*op));
			printInt(result);
			while(keypad_u8read()==0xFF);
			break;
		}
		else if((*f)=='A')
		{
			LCD_clearscreen();
			goto label;
		}
		else
		{
			LCD_clearscreen();
			LCD_vSend_string("Only 2 Operands");
			LCD_movecursor(2,1);
			LCD_vSend_string("Allowed !!");
			_delay_ms(1500);
			break;
		}
	}
	LCD_clearscreen();
	LCD_vSend_string("Bye Bye !");
}	


int readOperand(char *operand, char n, char *op)
{
	char inp='0xFF';
	while(1)
	{
		do
		{
			inp=keypad_u8read();
		} while(inp==0xFF);
		_delay_ms(250);
		if(inp<='9' && inp>='0')
		{
			(*operand) = inp;
			LCD_vSend_char(*operand);
		}
		else
		{
			(*op) = inp;
			break;
		}
		operand++;
		n++;
	}
	operand = operand-n;
	int value = charArrayToInt(operand,n);
	return value;
}


int charArrayToInt(char *arr, char n)
{
	int i, value, r, flag;
	
	//flag = 1; for -ve numbers
	i = value = 0;
	
	for(i=0; i<n; i++)
	{
		 // if arr contain negative number
		 /*
		 if( i==0 && arr[i]=='-' )
		 {
			 flag = -1;
			 continue;
		 }
		 */
		r = arr[i] - '0';
		value = value * 10 + r; //increase a zero in the right then add the value
	}
	
	//value = value * flag; // for -ve ops
	
	return value;
	
}

int operandtoInteger(char *operand, char n)
{
	int returnval=0;
	char i=0;
	for(i=0;i<n;i++)
	{
		returnval = returnval*10 + ((*(operand+i))-'0');
	}
	return returnval;
}


void printInt(int z)
{
	LCD_vSend_char(z/1000 + 48);
	LCD_vSend_char(((z/100)%10)+48);
	LCD_vSend_char(((z/10)%10)+48);
	LCD_vSend_char((z%10) + 48);
}

int calcResult(int x, int y, char op)
{
	if(op=='+')
	{
		return x+y;
	}
	else if(op=='-')
	{
		return x-y;
	}
	else if(op=='x')
	{
		return x*y;
	}
	else if(op='/')
	{
		return x/y;
	}
	else
	{
		LCD_clearscreen();
	}
}
