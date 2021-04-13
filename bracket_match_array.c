#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element;

#define MAXSIZE 100

element stack[MAXSIZE];
int top = -1;


int isempty() {
	return (top == -1);
}

int isfull() {
	return (top == MAXSIZE - 1);
}
void push(element item) {
	if (isfull()) {
		printf("가득참");
		exit(1);
	}
	else
		stack[++top] = item;
}

element pop() {

	if (isempty()) {
		printf("stack is empty\n");
		exit(1);
	}
	else {
		return stack[top--];
	}
}

int testPair(char *exp) {
	char symbol, openpair;
	int length = strlen(exp);

	for (int i = 0; i < length; i++) {
		symbol = exp[i];
		switch (symbol) {
		case'(':case'{':case'[':
			push(symbol);
			break;
		case')':case'}':case']':
			if (top == -1)return 0;
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
	if (top == -1)return 1;
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
