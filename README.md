Name: Yousif Kako

Queue:
	Acquires Two(2) Structs:
		struct Node:
			float time
			struct Node* next
		
		struct Queue:
			struct Node* front
			struct Node* last
			unsigned int size
	
	float initQueue(Queue* queue):
		Is a function that initializes the passed in queue.
	
	float front(Queue* queue) AND last(Queue* queue):
		These two functions where only used in the testing of this "Queue" library.

	Void EnQueue(Queue* queue, float time):
		This EnQueue function checks the size of the queue, if it is empty then it would
		make allocate the front Node and utilize that space. If it is not empty, it would
		allocate to the last Nodes next element and utilize that space. Then it would
		increment the size (The Actual Variable "Size") of the queue.

	Node* DeQueue(Queue* queue):
		It first decrements the size (The Actual Variable "Size"), then we create a temporary Node pointer
		to store the front Node, then we point the front Node to the temporary Nodes next (Which is the 
		front Nodes next). Finally, we return the temporary Node.


Heap:
	Acquires Two(2) Structs:
		struct HeapNode:
			unsigned int id
			float time
			struct HeapNode* next
		
		struct Heap:
			struct HeapNode* FrontNode
			struct HeapNode* LastNode
			unsigned int size

	void initHeap(Heap* heap):
		Is a function that initializes the passed in heap.

	void addToHeap(Heap* heap, int id, float time):
		This functions creates a new Node "tmp", I config the the jobNumber, id, and time. Then
		it checks if the heap is empty, if so then we add the new Node to the front, else we
		go through the heap and check where if fits.

	HeapNode* removeFromHeap(Heap* heap):
		It first decrements the size (The Actual Variable "Size"), then we create a temporary
		HeapNode pointer to store the front Node, then we point the front Node to the temporary
		Nodes next (Which is the front Nodes next). Finally, we return the temporary HeapNode.


Configuration File Reader:
	#define LINE_LENGTH 20:
		This is the length of the line that I would be reading from and writing to.

	struct ConfigData
		char* names
		float* times

	ConfigData render(FILE* logFile):
		This function loops through the config.txt file to read each line and append them to my
		names and times pointer arrays in the struct "ConfigData". I also log all of the configs
		that where read in. Then we return the struct "ConfigData".


Main:
	The Main.c File contains all of the comments needed. I did this because I wanted to explain each part
	by it self.