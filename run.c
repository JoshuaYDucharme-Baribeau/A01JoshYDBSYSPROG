/*Logic for main program*/
//Only cryptoMagic.c should use run.c, but run.c will use almost everything else


#include <stdio.h>

#include "run.h"

#include "userInterface.h"
#include "fileHandler.h"
#include "encrypter.h"
#include "decrypter.h"

void run(char[9] runMode, char[] fileName)
{
	//verify that the file exists

	if(checkFileExistence(fileName))
	{
		if(argv[1] == "-encrypt") 
		{
			//run encrypter
			printf("status of encryption: ", encryption(fileName));
		}
		else if(argv[1] == "-decrypt")
		{
			//run decrypter
			printf("status of decryption: ", decryption(fileName));
			//decryption(fileName);
		}
	}
	else {
		//should try to get more specific error handling, but low priority
		displayError("The file name you have entered does not exist in the specified directory or cannot be read.");
	}

}