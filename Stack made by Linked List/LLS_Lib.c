#include "LLS_H.h"


//스택 만들기
void LLS_CreateStack(LLS** Stack) {
	(*Stack) = (LLS*)malloc(sizeof(LLS));
	(*Stack)->List = NULL;
	(*Stack)->Top = NULL;
}

//노드 만들기
Node* LLS_CreateNode(char* NewData) {
	Node* NewNode = (Node*)malloc(sizeof(Node));
	NewNode->Data = (char*)malloc(strlen(NewData) + 1);
	strcpy(NewNode->Data, NewData);
	NewNode->NextNode = NULL;
	return NewNode;
}

//노드 푸쉬
void LLS_Push(LLS* Stack, Node* NewNode) {
	if (Stack->List == NULL)
		Stack->List = NewNode;
	else
		Stack->Top->NextNode = NewNode;

	Stack->Top = NewNode;
}

//노드 팝
Node* LLS_Pop(LLS* Stack) {
	Node* TopNode = Stack->Top;
	if (Stack->List == TopNode) {
		Stack->Top = NULL;
		Stack->List = NULL;
	}
	else {
		Node* CurrentNode = Stack->List;
		while (CurrentNode->NextNode != TopNode)
			CurrentNode = CurrentNode->NextNode;
		Stack->Top = CurrentNode;
		CurrentNode->NextNode = NULL;
	}
	return TopNode;
}

//탑 반환
Node* LLS_Top(LLS* Stack) {
	return Stack->Top;
}

// 스택이 비어 있는지
int LLS_IsEmpty(LLS* Stack) {
	return (Stack->List == NULL);
}

// 스택의 크기
int LLS_GetSize(LLS* Stack) {
	int cnt;
	Node* CurrentNode = Stack->List;
	for (cnt = 0; CurrentNode != NULL; cnt++)
		CurrentNode = CurrentNode->NextNode;
	return cnt;
}

//노드 삭제
void LLS_DestroyNode(Node* Node) {
	free(Node->Data);
	free(Node);
}

//스택 삭제
void LLS_DestroyStack(LLS* Stack) {
	while (!LLS_IsEmpty(Stack)) {
		Node* Popped = LLS_Pop(Stack);
		LLS_DestroyNode(Popped);
	}
	free(Stack);
}