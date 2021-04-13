#include <stdio.h>
#include <stdlib.h>
#define Max_StackSize 100

// 배열 스택

//typedef struct stack {
//	int key;
//}element;

 //typedef int element;

int stack[Max_StackSize];
int top = -1;

int is_empty() {
	return (top == -1);
}

int is_full() {
	return (top == (Max_StackSize - 1));
}

void push(int item) {
	if (is_full()) {
		printf("Stack is full\n");
		exit(1);
	}
	else
		stack[++top]=item;
}

int pop() {
	if (is_empty()) {
		printf("Stack is empty\n");
		exit(1);
	}
	else
		return stack[top--];
}

void print() {
	printf("[ ");;
	for (int i = 0; i <= top; i++) {
		printf("%d ", stack[i]);
	}
	printf("]\n");
}

int main(void) {

	int item;
	printf("스택 연산\n");
	print();
	push(1); print();
	push(2); print();
	push(3); print();

	item = pop(); print();
	printf("\tpop=> %d\n", item);
	item = pop(); print();
	printf("\tpop=> %d\n", item);
	item = pop(); print();
	printf("\tpop=> %d\n", item);
}