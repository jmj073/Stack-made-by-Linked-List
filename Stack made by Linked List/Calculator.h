#ifndef CALULATOR_H
#define CALULATOR_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "LLS_H.h"

typedef enum {
	L_PRTS = '(', R_PRTS = ')',
	PLUS = '+', MINUS = '-',
	MULTIPLY = '*', DIVIDE = '/',
	SPACE = ' ', OPERAND
} SYMBOL;

int IsNumber(char Cipher);
unsigned int GetNextToken(char* Expression, char* Token, int* TYPE);
int GetPriority(char Operator, int InStack);
int IsPrior(char Operator1, char Operator2);
void GetPostfix(char* InfixExpression, char* PostfixExpression);
double Calculate(char* PostfixExpression);

#endif //CALULATOR_H