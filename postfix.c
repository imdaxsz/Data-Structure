#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//���Ḯ��Ʈ

typedef int element;
// item�� int�� �ϳ� ���� ���� �Ἥ element�� �ϳ� ��� ����

typedef struct stacknode {
	element item;
	struct stacknode* link;
}stacknode;

stacknode* top;

int isempty() {
	if (top == NULL)return 1;
	else
		return 0;
}

void push(element item) {
	stacknode* temp = (stacknode*)malloc(sizeof(stacknode));
	temp->item = item;
	temp->link = top;
	top = temp;
}

element pop() {
	element item;
	stacknode* temp = top;

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

element evalPostfix(char *exp) {
	int opr1, opr2, value;
	int length = strlen(exp);
	char symbol;
	top = NULL;

	for (int i = 0; i < length; i++) {
		symbol = exp[i];
		if (symbol != '+'&&symbol != '-'&&symbol != '*'&&symbol != '/') {
			value = symbol - '0';
			push(value);
		}
		else {
			opr2 = pop();
			opr1 = pop();

			switch (symbol) {
			case'+':push(opr1 + opr2); break;
			case'-':push(opr1 - opr2); break;
			case'*':push(opr1 * opr2); break;
			case'/':push(opr1 / opr2); break;
			}
		}
	}

	return pop();
}

void main() {
	int result;
	char* express = "35*62/-";
	printf("���� ǥ��� : %s\n\n", express);

	result = evalPostfix(express);
	printf("���� ��� => %d", result);

}