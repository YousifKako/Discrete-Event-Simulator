#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void initHeap(Heap* heap)
{
	heap->FrontNode = NULL;
	heap->size = 0;
}

void addToHeap(Heap* heap, int jobNumber, int id, float time)
{
	HeapNode* tmp = (HeapNode *)malloc(sizeof(HeapNode));
	tmp->jobNumber = jobNumber;
	tmp->id = id;
	tmp->time = time;
	tmp->next = NULL;

	if (heap->size == 0)
	{
		heap->FrontNode = tmp;
	}
	else
	{
		HeapNode* current = heap->FrontNode;
		HeapNode* prev = NULL;

		while (current != NULL)
		{
			if (time < current->time)
			{
				tmp->next = current;
				if (prev == NULL)
				{
					heap->FrontNode = tmp;
				}
				else
				{
					prev->next = tmp;
				}

				break;
			}

			prev = current;
			current = current->next;
		}

		if (current == NULL)
		{
			prev->next = tmp;
		}
	}

	heap->size++;
}

HeapNode* removeFromHeap(Heap* heap)
{
	heap->size--;

	HeapNode* tmp = heap->FrontNode;
	heap->FrontNode = tmp->next;

	return tmp;
}