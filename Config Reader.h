#ifndef RENDER_H
#define RENDER_H

typedef struct ConfigData
{
	char* names;
	float* times;
}ConfigData;

ConfigData render(FILE* logFile);

#endif // RENDER_H