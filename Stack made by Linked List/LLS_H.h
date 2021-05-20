#ifndef LLS_H
#define LLS_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include<string.h>

//�������� �ڷ�����  ĳ���� �����ͷ� ����
typedef struct tagNode {
	char* Data;
	struct tagNode* NextNode;
} Node;

typedef struct tagLinkedListStack {
	Node* List;
	Node* Top;
} LLS;

//���� �����
void LLS_CreateStack(LLS** Stack);
//��� �����
Node* LLS_CreateNode(char* NewData);
//��� Ǫ��
void LLS_Push(LLS* Stack, Node* NewNode);
//��� ��
Node* LLS_Pop(LLS* Stack);
//ž ��ȯ
Node* LLS_Top(LLS* Stack);
// ������ ��� �ִ���
int LLS_IsEmpty(LLS* Stack);
// ������ ũ��
int LLS_GetSize(LLS* Stack);
//��� ����
void LLS_DestroyNode(Node* Node);
//���� ����
void LLS_DestroyStack(LLS* Stack);

#endif //LLS_H