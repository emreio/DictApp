#pragma once
#include<stdio.h>

FILE* openFileForRead(char *fileName);
FILE* createNewFileForWrite(char* fileName);
FILE* openFileForAppend(char* fileName);
int getLinesCount(FILE* file);