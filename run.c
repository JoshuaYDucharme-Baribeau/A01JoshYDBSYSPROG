/*Logic for main program*/
//Only cryptoMagic.c should use run.c, but run.c will use almost everything else


#include <stdio.h>
#include <string.h>

#include "run.h"

#include "userInterface.h"
#include "fileHandler.h"
#include "encrypter.h"
#include "decrypter.h"

int run(char *runMode, char *fileName)
{
	//verify that the file exists

	if(checkFileExistence(fileName))
	{
		if(strcmp(runMode, "-encrypt") == 0)
		{
			//run encrypter
			//encrypted characters[] = readForEncryption(fileName);
			printf("status of encryption: %s\n", encryption(fileName));
		}
		else if(strcmp(runMode, "-decrypt") == 0)
		{
			//run decrypter
			printf("status of decryption: %s\n", decryption(fileName));
			//decryption(fileName);
		}
	}
	else {
		//should try to get more specific error handling, but low priority
		displayError("The file name you have entered does not exist in the specified directory or cannot be read.\n");
	}

	return (0);

}