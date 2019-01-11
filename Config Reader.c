#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 20

typedef struct ConfigData
{
	char* names;
	float* times;
}ConfigData;

ConfigData render(FILE* logFile)
{
	FILE* file;
	ConfigData configData;
	configData.names = (char *)malloc(sizeof(char) * 20);
	configData.times = (float *)malloc(sizeof(float) * 20);
	char line[LINE_LENGTH];
	file = fopen("Config.txt", "r");

	fprintf(logFile, "%s\n", "Configs:");

	for (int i = 0;  fgets(line, LINE_LENGTH, file) != NULL; )
	{
		if (line[0] != '\n')
		{
			char str[LINE_LENGTH];
			float num;

			sscanf(line, "%s %f", str, &num);
			configData.names[i] = *str;
			configData.times[i] = num;

			// Log Configs to File
			fprintf(logFile, "%s %0.1f\n", str, num);

			i++;
		}
	}

	fprintf(logFile, "\n");

	return configData;
}