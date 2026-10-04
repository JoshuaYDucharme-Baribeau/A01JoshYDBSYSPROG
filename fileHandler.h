#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <stdbool.h>

bool checkFileExistence(char *fileName);

char* readForEncryption(char* fileName);

void writeEncryption(char* fileName, char* outChar);

char* newFileName(char* fileName);

#endif