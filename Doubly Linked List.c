#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	struct node *pre;
	int data;
	struct node *next;
}Node;

Node* Insert(Node* head, int num) {

	Node *newnode= (Node*)malloc(sizeof(Node));
	newnode-> data = num;
	newnode->pre = NULL;
	newnode->next = NULL;

	if (head == NULL) {
		head = newnode;
	}
	else {
		//// ¸Ç ¾Õ¿¡ »ğÀÔ
		//head->pre = newnode;
		//newnode->next = head;
		//head = newnode;

		// ¸Ç µÚ¿¡ »ğÀÔ
		Node *temp = head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newnode;
		newnode->pre = temp;
	}
	return head;
}
//
void Display(Node *head) {
	Node *temp = head;
	/*while (temp->next != NULL) {
		printf("%d -> ", temp->data);
		temp = temp->next;
	}
	printf("%d",temp->data);
	printf("\n\n");*/

	while (temp!= NULL) {
		printf("%d ", temp->data);
		temp = temp->next;
		if (temp!= NULL) {
			printf("-> ");
		}
	}
	printf("\n\n");


	/*
	while (temp->pre != NULL) {
		printf("%d -> ", temp->data);
		temp = temp->pre;
	}
	printf("%d\n\n", temp->data);
	*/
}

Node* Delete(Node * head, int num) {

	if (head->data == num) {
		head = head->next;
		free(head->pre);
		head->pre = NULL;
	}
	else {
		Node *cur = head;
		while (cur->data != num)
			cur = cur->next;
		if (cur->next == NULL) {
			cur->pre->next = NULL;
		}
		else {
			cur->pre->next = cur->next;
			cur->next->pre = cur->pre;
		}

		free(cur);
	}

	return head;

}

void main() {

	Node *head = NULL;

	head = Insert(head, 1);
	head = Insert(head, 2);
	head = Insert(head, 3);
	head = Insert(head, 4);
	head = Insert(head, 5);
	Display(head);

	head = Delete(head, 1);
	head = Delete(head, 4);
	head = Delete(head, 5);
	Display(head);
}