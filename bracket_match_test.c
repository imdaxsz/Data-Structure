#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element;

typedef struct stackNode{
	element item;
	struct stackNode *link;
}stackNode;

stackNode *top;


int isempty() {
	if (top == NULL)return 1;
	else
		return 0;
}

void push(element item) {
	stackNode* temp = (stackNode*)malloc(sizeof(stackNode));
	temp->item = item;
	temp->link = top;
	top = temp;
}

element pop() {
	element item;
	stackNode* temp = top;

	if (top == NULL) {
		printf("stack is empty\n");
		return 0;
	}
	else {
		item = temp->item;
		top = temp->link;
		free(temp);
		return item;
	}
}

int testPair(char *exp) {
	char symbol, openpair;
	int length = strlen(exp);
	top = NULL;

	for (int i = 0; i < length; i++) {
		symbol = exp[i];
		switch (symbol) {
		case'(':case'{':case'[':
			push(symbol);
			break;
		case')':case'}':case']':
			if (top == NULL)return 0;
			else {
				openpair = pop();
				if ((openpair == '('&&symbol != ')') ||
					(openpair == '{'&&symbol != '}') ||
					(openpair == '['&&symbol != ']'))
					return 0;
				else
					break;
			}
		}
	}
	if (top == NULL)return 1;
	else return 0;
}

void main() {
	char* express = "{(A+B)-3}*5+[{cos(x+y)+7}-1]*4";
	printf("%s", express);

	if (testPair(express) == 1)
		printf("\n\n수식의 괄호가 맞게 사용되었습니다!");
	else
		printf("\n\n수식의 괄호가 틀렸습니다!");
}
