#ifndef QUEUE_H
#define QUEUE_H

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

void initQueue(Queue* queue);
float front(Queue* queue);
float last(Queue* queue);
void EnQueue(Queue* queue, int jobNumber, float time);
Node* DeQueue(Queue* queue);

#endif // QUEUE_H