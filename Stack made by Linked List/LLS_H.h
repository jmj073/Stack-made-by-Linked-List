#ifndef LLS_H
#define LLS_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include<string.h>

//데이터의 자료형을  캐릭터 포인터로 고정
typedef struct tagNode {
	char* Data;
	struct tagNode* NextNode;
} Node;

typedef struct tagLinkedListStack {
	Node* List;
	Node* Top;
} LLS;

//스택 만들기
void LLS_CreateStack(LLS** Stack);
//노드 만들기
Node* LLS_CreateNode(char* NewData);
//노드 푸쉬
void LLS_Push(LLS* Stack, Node* NewNode);
//노드 팝
Node* LLS_Pop(LLS* Stack);
//탑 반환
Node* LLS_Top(LLS* Stack);
// 스택이 비어 있는지
int LLS_IsEmpty(LLS* Stack);
// 스택의 크기
int LLS_GetSize(LLS* Stack);
//노드 삭제
void LLS_DestroyNode(Node* Node);
//스택 삭제
void LLS_DestroyStack(LLS* Stack);

#endif //LLS_H