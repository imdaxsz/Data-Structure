#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct queue {
	element data;
	struct queue* link;
}Queue;

Queue *front, *rear;

int isempty() {
	return (rear == NULL);
}

void enqueue(element data) {
	Queue *new = (Queue *)malloc(sizeof(Queue));
	new->data = data;
	new->link = NULL;
	if (isempty()) {
		front = new;
		rear = new;
	}
	else {
		rear->link = new;
		rear = new;
	}
}

element dequeue() {
	if (isempty()) {
		printf("비었음");
		exit(1);
	}
	else {
		Queue *temp = front;
		front = front->link;
		element item = temp->data;
		if (front == NULL)
			rear = NULL;
		free(temp);

		return item;
	}
}

void print() {
	Queue *temp = front;
	printf("[");
	if (temp != NULL) {
		while ((temp != rear)) {
			printf("%d ", temp->data);
			temp = temp->link;
		}
		printf("%d", temp->data);
	}

	printf("]\n");
}

int main(void) {
	element data;
	front = rear = NULL;

	printf("연결 큐 연산\n");
	print();
	enqueue(1); print();
	enqueue(2); print();
	enqueue(3); print();
	enqueue(4); print();

	data = dequeue(); print();
	data = dequeue(); print();
	data = dequeue(); print();
	data = dequeue(); print();
}