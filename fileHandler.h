#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <stdbool.h>

bool checkFileExistence(char *fileName);

char* readFile(char* fileName, int crypto_mode);

void writeEncryption(char* fileName, char* outChar);

char* newFileName(char* fileName);

char* newDecryptedFileName(char* fileName);

void writeDecrypted(char* fileName, char* outChar);

#endif