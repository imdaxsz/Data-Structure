#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int coef;
	int expo;
	struct node* link;
}Node;

typedef struct list{
	int length;
	Node* head;
	Node* tail;
}List;

void init(List *plist) {
	plist->length = 0;
	plist->head = plist->tail = NULL;
}

void insertnode(List *plist, int coef, int expo) {
	Node *newnode = (Node *)malloc(sizeof(Node));
	newnode->coef = coef;
	newnode->expo = expo;
	newnode->link = NULL;
	
	if (plist->tail == NULL) {
		plist->head=plist->tail = newnode;
	}
	else {
		plist->tail->link = newnode;
		plist->tail = newnode;
	}
	plist->length++;
}

void display(List *plist) {
	Node *temp = plist->head;
	for (; temp; temp = temp->link) {
		printf("%dx^%d", temp->coef, temp->expo);
		if (temp->link != NULL) {
			printf(" + ");
		}
	}
	printf("\n\n");
}

void add(List *A, List *B, List *C) {
	Node *a = A->head;
	Node *b = B->head;
	int sum;
	while (a&&b) {
		if (a->expo > b->expo) {
			insertnode(C, a->coef, a->expo);
			a = a->link;
		}
		else if (a->expo == b->expo) {
			sum = a->coef + b->coef;
			if(sum!=0)
				insertnode(C, sum, a->expo);
			a = a->link; b = b->link;
		}
		else {
			insertnode(C, b->coef, b->expo);
			b = b->link;
		}
	}

	for (; a != NULL; a = a->link)
		insertnode(C, a->coef, a->expo);
	for (; b != NULL; b = b->link)
		insertnode(C, b->coef, b->expo);
}

void main() {

	List A, B, C;
	init(&A); init(&B); init(&C);
	insertnode(&A, 3, 5);
	insertnode(&A, 4, 3);
	insertnode(&A, 7, 1);
	printf("A(x) = ");
	display(&A);

	insertnode(&B, 8, 4);
	insertnode(&B, 1, 2);
	insertnode(&B, 2, 1);
	printf("B(x) = ");
	display(&B);

	add(&A, &B, &C);
	printf("C(x) = ");
	display(&C);

}