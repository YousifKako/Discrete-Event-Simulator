#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Queue.h"
#include "Heap.h"
#include "Config Reader.h"

float SEED;
float INIT_TIME;
float FIN_TIME;
float ARRIVE_MIN;
float ARRIVE_MAX;
float QUIT_PROB;
float CPU_MIN;
float CPU_MAX;
float DISK1_MIN;
float DISK1_MAX;
float DISK2_MIN;
float DISK2_MAX;

void dataConfig(FILE* logFile)
{
	ConfigData configs = render(logFile);

	SEED = configs.times[0];
	INIT_TIME = configs.times[1];
	FIN_TIME = configs.times[2];
	ARRIVE_MIN = configs.times[3];
	ARRIVE_MAX = configs.times[4];
	QUIT_PROB = configs.times[5];
	CPU_MIN = configs.times[6];
	CPU_MAX = configs.times[7];
	DISK1_MIN = configs.times[8];
	DISK1_MAX = configs.times[9];
	DISK2_MIN = configs.times[10];
	DISK2_MAX = configs.times[11];
}

int main()
{
	// Meaning of ID Numbers
	// 1 : Heap Go-To CPU
	// 2 : Finished at CPU
	// 3 : Disk1 Queue
	// 4 : Disk2 Queue
	
	// Read Config File, Config Data
	FILE* logFile;

	// Clear Log File
	fclose(fopen("Log File.txt", "w"));

	// Open it For Append
	logFile = fopen("Log File.txt", "a+");
	dataConfig(logFile);
	srand(SEED);
	Queue cpu;
	initQueue(&cpu);
	Queue disk1;
	initQueue(&disk1);
	Queue disk2;
	initQueue(&disk2);

	int jobNumber = 0;
	float jobTime = 0;
	float cpuTime = 0;
	float disk1Time = 0;
	float disk2Time = 0;

	float timeServerBusy = 0;

	// Queue Size
	int queueSize = 0;
	float averQueueSize = 0;
	
	// Average and Maximum Response Time
	float maxResponse = 0;
	float aveResponse = 0;
	float totalResponse = 0;

	// Add INIT_TIME and FIN_TIME to Heap
	Heap heap;
	initHeap(&heap);
	addToHeap(&heap, 0, 1, INIT_TIME);
	addToHeap(&heap, -1, 1, FIN_TIME);

	// Create/Remove Jobs
	while (heap.size)
	{
		// Start the Job at the Top of the Heap
		HeapNode* tmp = removeFromHeap(&heap);
		// printf("%f\n", tmp->time);
		fprintf(logFile, "Job[%d]: Removed From the Top of The Queue/Heap - TIME: %0.1f\n", tmp->jobNumber, tmp->time);
		
		if (tmp->time == FIN_TIME)
			break;

		jobNumber++;
		jobTime += rand() % (int)(ARRIVE_MAX - ARRIVE_MIN);
		addToHeap(&heap, jobNumber, 1, jobTime);
		fprintf(logFile, "Job[%d]: A New Job Has Been Added to Job Queue/Heap - TIME: %0.1f\n", jobNumber, jobTime);
		// printf("Job Removed From the Top of The Queue / Heap - TIME: %0.1f\n", jobTime);


		// In Heap Go-To CPU
		if (tmp->id == 1)
		{
			// Gen CPU Time and Add to CPU Queue
			cpuTime += rand() % (int)(CPU_MAX - CPU_MIN);
			EnQueue(&cpu, tmp->jobNumber, cpuTime);

			// Add Job Queue/Heap
			addToHeap(&heap, tmp->jobNumber, 2, cpuTime);
			
			fprintf(logFile, "Job[%d]: Entered CPU Queue - TIME: %0.1f\n", tmp->jobNumber, cpuTime);

			// Maximum Response Time
			totalResponse += jobTime - tmp->time;
			if ((jobTime - tmp->time) > maxResponse)
				maxResponse = jobTime - tmp->time;
		}

		// Finished at CPU Check to Exit or Not
		else if (tmp->id == 2)
		{
			Node* exitCPU = DeQueue(&cpu);
			timeServerBusy += (cpuTime - exitCPU->time);
			float exit = rand() % 100;

			fprintf(logFile, "Job[%d]: Left CPU... Waiting to Exit or Go-To Disk Queue\n", exitCPU->jobNumber);

			if (exit/100 <= QUIT_PROB)
			{
				// Job is Done Exit Program and Log to File
				fprintf(logFile, "Job[%d]: Exited the Simulation - Probibility: %f\n", exitCPU->jobNumber, exit/100);

				// Print Statistics
				// float averageTime = jobTime - tmp->time;
				// float MaximumTime = tmp->time;
				// printf("Average Time: %0.1f | Maximum Time: %0.1f\n", averageTime, MaximumTime);
				continue;
			}

			else
			{
				// Put in Disk 1
				if (disk1.size <= disk2.size)
				{
					// Gen Disk 1 Time and Add to Disk 1 Queue
					disk1Time += rand() % (int)(DISK1_MAX - DISK1_MIN);
					EnQueue(&disk1, exitCPU->jobNumber, disk1Time);

					// Add to Job Queue/Heap
					addToHeap(&heap, exitCPU->jobNumber, 3, disk1Time);

					fprintf(logFile, "Job[%d]: Did Not Exit... Sending Job to Disk 1 - TIME: %0.1f\n", exitCPU->jobNumber, disk1Time);
				}

				// Put in Disk 2
				else
				{
					// Gen Disk 2 Time and Add to Disk 2 Queue
					disk2Time += rand() % (int)(DISK2_MAX - DISK2_MIN);
					EnQueue(&disk2, exitCPU->jobNumber, disk2Time);

					// Add to Job Queue/Heap
					addToHeap(&heap, exitCPU->jobNumber, 4, disk2Time);

					fprintf(logFile, "Job[%d]: Did Not Exit... Sending Job to Disk 2 - TIME: %0.1f\n", exitCPU->jobNumber, disk2Time);
				}
			}

			free(exitCPU);
		}

		// At Disk1 Go-To CPU
		else if (tmp->id == 3)
		{
			// DeQueue From Disk 1
			Node* exitDisk1 = DeQueue(&disk1);

			// Gen Disk 1 Time and Add to CPU
			cpuTime += rand() % (int)(ARRIVE_MAX - ARRIVE_MIN);
			EnQueue(&cpu, exitDisk1->jobNumber, cpuTime);

			// Add to Job Queue/Heap
			addToHeap(&heap, exitDisk1->jobNumber, 2, cpuTime);

			fprintf(logFile, "Job[%d]: Leaving Disk 1 Going to CPU - TIME: %0.1f\n", exitDisk1->jobNumber, cpuTime);

			free(exitDisk1);
		}

		// At Disk2 Go-To CPU
		else if (tmp->id == 4)
		{
			// DeQueue From Disk 2
			Node* exitDisk2 = DeQueue(&disk2);

			// Gen Disk 2 Time and Add to CPU
			cpuTime += rand() % (int)(ARRIVE_MAX - ARRIVE_MIN);
			EnQueue(&cpu, exitDisk2->jobNumber, cpuTime);

			// Add to Job Queue/Heap
			addToHeap(&heap, exitDisk2->jobNumber, 2, cpuTime);

			fprintf(logFile, "Job[%d]: Leaving Disk 2 Going to CPU - TIME: %0.1f\n", exitDisk2->jobNumber, cpuTime);

			free(exitDisk2);
		}

		// printf("%f\n", tmp->time);
		free(tmp);
	}

	fprintf(logFile, "Simulation Has Ended.\n\n\n");

	// Statistics

	// To Log File
	fprintf(logFile, "Statistics\n\n");
	// Queue Size
	fprintf(logFile, "Queue Size\n");
	queueSize = cpu.size;
	averQueueSize = (float)jobNumber / queueSize;
	fprintf(logFile, "\tAverage Queue Size: %0.1f\n", averQueueSize);
	fprintf(logFile, "\tMaximum Queue Size: %d\n\n", queueSize);
	// Server Ulilization
	float serverUtilization = timeServerBusy / (FIN_TIME - INIT_TIME);
	fprintf(logFile, "Utilization:\n");
	fprintf(logFile, "\tThe Utilization of Each Server (Component): %0.1f\n\n", serverUtilization);
	// Response Time
	fprintf(logFile, "Response Time:\n");
	aveResponse = totalResponse / maxResponse;
	fprintf(logFile, "\tAverage Response Time: %0.1f\n", aveResponse);
	fprintf(logFile, "\tMAXimum Response Time: %0.1f\n\n", maxResponse);
	// Jobs Completed
	fprintf(logFile, "The Throughput of Each Server:\n");
	fprintf(logFile, "\tJobs Completed: %d\n", jobNumber);

	// To Screen
	printf("Statistics\n\n");
	printf("Queue Size\n");
	printf("\tAverage Queue Size: %0.1f\n", averQueueSize);
	printf("\tMaximum Queue Size: %d\n\n", queueSize);
	printf("Utilization:\n");
	printf("\tThe Utilization of Each Server (Component): %0.1f\n\n", serverUtilization);
	printf("Response Time:\n");
	printf("\tAverage Response Time: %0.1f\n", aveResponse);
	printf("\tMAXimum Response Time: %0.1f\n\n", maxResponse);
	printf("The Throughput of Each Server:\n");
	printf("\tJobs Completed: %d\n", jobNumber);
	


	// Close Log File
	fclose(logFile);

	system("pause");

	return 1;
}