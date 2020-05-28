#ifndef PARAMS_T__H
#define PARAMS_T__H

#define MAX_SIZE_PREFIX 1024

typedef struct params_t
{
	int i;
	int N;
	int M;
	FILE *inputStream;
	FILE *outputStream;
	char *prefix;
} params_t;

#endif