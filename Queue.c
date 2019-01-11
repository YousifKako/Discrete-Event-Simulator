#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int jobNumber;
	float time;
	struct Node* next;
}Node;

typedef struct Queue
{
	struct Node* front;
	struct Node* last;
	unsigned int size;
}Queue;

void initQueue(Queue* queue)
{
	queue->front = NULL;
	queue->last = NULL;
	queue->size = 0;
}

float front(Queue* queue)
{
	return queue->front->time;
}

float last(Queue* queue)
{
	return queue->last->time;
}

void EnQueue(Queue* queue, int jobNumber, float time)
{
	if (queue->size == 0)
	{
		queue->front = (Node *) malloc(sizeof(Node));
		queue->front->jobNumber = jobNumber;
		queue->front->time = time;
		queue->last = queue->front;
	}

	else
	{
		queue->last->next = (Node *) malloc(sizeof(Node));
		queue->last->next->jobNumber = jobNumber;
		queue->last->next->time = time;
		queue->last = queue->last->next;
	}

	queue->size++;
}

Node* DeQueue(Queue* queue)
{
	queue->size--;

	Node* tmp = queue->front;
	queue->front = tmp->next;

	return tmp;
}