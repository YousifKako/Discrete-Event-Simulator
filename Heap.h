#ifndef HEAP_H
#define HEAP_H

typedef struct HeapNode
{
	int jobNumber;
	unsigned int id;
	float time;
	struct HeapNode* next;
}HeapNode;

typedef struct Heap
{
	struct HeapNode* FrontNode;
	unsigned int size;
}Heap;

void initHeap(Heap* heap);
void addToHeap(Heap* heap, int jobNumber, int id, float time);
HeapNode* removeFromHeap(Heap* heap);

#endif // HEAP_H