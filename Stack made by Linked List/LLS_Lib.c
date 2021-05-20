#include "LLS_H.h"


//���� �����
void LLS_CreateStack(LLS** Stack) {
	(*Stack) = (LLS*)malloc(sizeof(LLS));
	(*Stack)->List = NULL;
	(*Stack)->Top = NULL;
}

//��� �����
Node* LLS_CreateNode(char* NewData) {
	Node* NewNode = (Node*)malloc(sizeof(Node));
	NewNode->Data = (char*)malloc(strlen(NewData) + 1);
	strcpy(NewNode->Data, NewData);
	NewNode->NextNode = NULL;
	return NewNode;
}

//��� Ǫ��
void LLS_Push(LLS* Stack, Node* NewNode) {
	if (Stack->List == NULL)
		Stack->List = NewNode;
	else
		Stack->Top->NextNode = NewNode;

	Stack->Top = NewNode;
}

//��� ��
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

//ž ��ȯ
Node* LLS_Top(LLS* Stack) {
	return Stack->Top;
}

// ������ ��� �ִ���
int LLS_IsEmpty(LLS* Stack) {
	return (Stack->List == NULL);
}

// ������ ũ��
int LLS_GetSize(LLS* Stack) {
	int cnt;
	Node* CurrentNode = Stack->List;
	for (cnt = 0; CurrentNode != NULL; cnt++)
		CurrentNode = CurrentNode->NextNode;
	return cnt;
}

//��� ����
void LLS_DestroyNode(Node* Node) {
	free(Node->Data);
	free(Node);
}

//���� ����
void LLS_DestroyStack(LLS* Stack) {
	while (!LLS_IsEmpty(Stack)) {
		Node* Popped = LLS_Pop(Stack);
		LLS_DestroyNode(Popped);
	}
	free(Stack);
}