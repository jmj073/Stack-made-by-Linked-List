#include "Calculator.h"

char NUMBER[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.' };

//�����ΰ�?
int IsNumber(char Cipher) {
	int i = 0;
	int ArrayLength = sizeof(NUMBER);

	for (i = 0; i < ArrayLength; i++)
		if (Cipher == NUMBER[i])
			return 1;
	return 0;
}

//��ū ���
unsigned int GetNextToken(char* Expression, char* Token, int* TYPE) {
	unsigned int i;

	for (i = 0; Expression[i]; i++) {
		Token[i] = Expression[i];

		if(IsNumber(Expression[i])) {
			*TYPE = OPERAND;
			if (!IsNumber(Expression[i + 1]))
				break;
		}
		else {
			*TYPE = Expression[i];
			break;
		}
	}

	Token[++i] = '\0';
	return i;
}

//�켱���� ���
int GetPriority(char Operator, int InStack) {
	int Priority = -1;

	switch (Operator) {
	case L_PRTS:
		if (InStack)
			Priority = 3;
		else
			Priority = 0;
		break;
	case MULTIPLY:
	case DIVIDE:
		Priority = 1;
		break;
	case PLUS:
	case MINUS:
		Priority = 2;
		break;
	}
	return Priority;
}

//�켱���� ��
int IsPrior(char OperatorInStack, char OperatorInToken) {
	return (GetPriority(OperatorInStack, 1) > GetPriority(OperatorInToken, 0));
}

//���� ǥ�⸦ ���� ǥ��� ��ȯ
void GetPostfix(char* InfixExpression, char* PostfixExpression) {
	LLS* Stack;
	
	char Token[32];
	int Type = -1;
	unsigned int Position = 0;
	unsigned int Length = strlen(InfixExpression);

	LLS_CreateStack(&Stack);

	while (Position < Length) {
		Position += GetNextToken(&InfixExpression[Position], Token, &Type);

		if (Type == OPERAND) {
			strcat(PostfixExpression, Token);
			strcat(PostfixExpression, " ");
		}
		else if (Type == R_PRTS) {
			while (!LLS_IsEmpty(Stack)) {
				Node* Popped = LLS_Pop(Stack);
				if (Popped->Data[0] == L_PRTS) {
					LLS_DestroyNode(Popped);
					break;
				}
				else {
					strcat(PostfixExpression, Popped->Data);
					LLS_DestroyNode(Popped);
				}
			}
		}
		else {
			while (!LLS_IsEmpty(Stack) && !IsPrior(LLS_Top(Stack)->Data[0], Token[0])) {
				Node* Popped = LLS_Pop(Stack);
				if (Popped->Data[0] != L_PRTS)
					strcat(PostfixExpression, Popped->Data);
				LLS_DestroyNode(Popped);
			}
			LLS_Push(Stack, LLS_CreateNode(Token));
		}
	}

	while (!LLS_IsEmpty(Stack)) {
		Node* Popped = LLS_Pop(Stack);

		if(Popped->Data[0] != L_PRTS)
			strcat(PostfixExpression, Popped->Data);
		LLS_DestroyNode(Popped);
	}
	LLS_DestroyStack(Stack);
}

//���� ǥ�⸦ ���
double Calculate(char* PostfixExpression) {
	LLS* Stack;
	Node* ResultNode;

	double Result;
	char Token[32];
	int Type = -1;
	unsigned int Read = 0;
	unsigned int Length = strlen(PostfixExpression);

	LLS_CreateStack(&Stack);

	while (Read < Length) {
		Read += GetNextToken(PostfixExpression + Read, Token, &Type);
		if (Type == SPACE)
			continue;
		if(Type == OPERAND) 
			LLS_Push(Stack, LLS_CreateNode(Token));
		else {
			char ResultString[32];
			double Operand1, Operand2, TempResult;
			Node* OperandNode;

			OperandNode = LLS_Pop(Stack);
			Operand2 = atof(OperandNode->Data);
			LLS_DestroyNode(OperandNode);

			OperandNode = LLS_Pop(Stack);
			Operand1 = atof(OperandNode->Data);
			LLS_DestroyNode(OperandNode);

			switch (Type)
			{
			case PLUS: TempResult = Operand1 + Operand2; break;
			case MINUS: TempResult = Operand1 - Operand2; break;
			case MULTIPLY: TempResult = Operand1 * Operand2; break;
			case DIVIDE: TempResult = Operand1 / Operand2; break;
			}

			_gcvt(TempResult, 10, ResultString);
			LLS_Push(Stack, LLS_CreateNode(ResultString));
		}
	}
	ResultNode = LLS_Pop(Stack);
	Result = atof(ResultNode->Data);
	LLS_DestroyNode(ResultNode);

	LLS_DestroyStack(Stack);

	return Result;
}