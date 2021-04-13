#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node *next;
}Node;

Node* Insert(Node *tail, int num) {
	Node *newnode = (Node *)malloc(sizeof(Node));
	newnode->data = num;

	if (tail == NULL) {
		tail = newnode;
		newnode->next = newnode; // 중요
	}
	else {
		newnode->next=tail->next;
		tail->next = newnode;
		tail = newnode; // 맨마지막인가 맨앞인가를 결정
	}

	return tail;
}

void Display(Node *tail) {
	Node *temp = tail->next;

	while (temp != tail) {
		printf("%d -> ", temp->data);
		temp = temp->next;
	}
	printf("%d\n\n", temp->data);
}

void main() {
	Node *tail = NULL;

	tail = Insert(tail, 1);
	tail = Insert(tail, 2);
	tail = Insert(tail, 3);
	tail = Insert(tail, 4);
	tail = Insert(tail, 5);

	Display(tail);
}