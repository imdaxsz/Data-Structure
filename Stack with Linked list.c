#include <stdio.h>
#include <stdlib.h>

//typedef int element;
// item을 int로 하나 위의 문장 써서 element로 하나 결과 동일

typedef struct stacknode {
	int item;
	struct stacknode* link;
}stacknode;

stacknode* top;

int isempty() {
	if (top == NULL)return 1;
	else
		return 0;
}

void push(int item) {
	stacknode* temp = (stacknode*)malloc(sizeof(stacknode));
	temp->item = item;
	temp->link = top;
	top = temp;
}

int pop() {
	int item;
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

void printstack() {
	stacknode* p = top;
	printf("[ ");
	while (p) {
		printf("%d ", p->item);
		p = p->link;
	}
	printf("]\n");
}

void main() {
	int item;
	top = NULL;
	printf("**스택 연산**\n\n");
	printstack();
	push(1); printstack();
	push(2); printstack();
	push(3); printstack();

	item = pop(); printstack();
	printf("\tpop=> %d\n", item);
	item = pop(); printstack();
	printf("\tpop=> %d\n", item);
	item = pop(); printstack();
	printf("\tpop=> %d\n", item);
}