//Logic for main program
//Only cryptoMagic.c should use run.c, but run.c will use almost everything else


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "run.h"

#include "userInterface.h"
#include "fileHandler.h"
#include "encrypter.h"
#include "decrypter.h"

int run(char *runMode, char *fileName)
{
	char* outChar;
	//verify that the file exists
	if(checkFileExistence(fileName))
	{
		if(strcmp(runMode, "-encrypt") == 0)
		{
			//run encrypter
			outChar = readFile(fileName, 1);
			if (!outChar)
			{
				displayError("Something went wong while encrypting");
				return 1;
			}
			
			//write the encrypted file
			writeEncryption(fileName, outChar);
			//free the memory			
			free(outChar);
		}
		else if(strcmp(runMode, "-decrypt") == 0)
		{
			outChar = readFile(fileName, 2);
			if (!outChar)
			{
				displayError("Something went wong while decrypting");
				return 1;
			}

			writeDecrypted(fileName, outChar);

			free(outChar);
		}
	}
	else 
	{
		//should try to get more specific error handling, but low priority
		displayError("The file name you have entered does not exist in the specified directory or cannot be read.\n");
	}
	return (0);
}