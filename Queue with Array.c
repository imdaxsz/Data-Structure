#include <stdio.h>
#include <stdlib.h>

typedef int element;

#define QUEUEMAXSIZE 8
element queue[QUEUEMAXSIZE];

int front = 0;
int rear = 0;

int isempty() {
	return(front == rear);
}

int isfull() {
	return(front == (rear + 1) % QUEUEMAXSIZE);
}

void enqueue(element data) {
	if (isfull()) {
		printf("포화");
		exit(1);
	}
	else{
		rear = (rear + 1) % QUEUEMAXSIZE;
		queue[rear] = data;
	}
}

element dequeue() {
	if (isempty()) {
		printf("공백");
		exit(1);
	}
	else {
		front = (front + 1) % QUEUEMAXSIZE;
		return queue[front];
	}
}

void print() {
	for (int i = front+1;i<=rear;i++)
		printf("%d ", queue[i]);
	printf("\n");
}

int main(void) {

	int item;

	printf("큐 연산\n");

	enqueue(1); print();
	enqueue(3); print();
	enqueue(2); print(); 
	enqueue(4); print();
	
	item=dequeue(); print(); 
	item=dequeue(); print(); 
	item=dequeue(); print();
	item=dequeue(); print();
}