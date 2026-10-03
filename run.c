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
	FILE* p_file = NULL;

	p_file = fopen(fileName, "r");
	
	if(p_file == NULL)
	{
		displayError("The file name you have entered does not exist in the specified directory or cannot be read.");
	}
	else {

		if(argv[1] == "-encrypt") 
		{
			//run encrypter

		}
		else if(argv[1] == "-decrypt")
		{
			//run decrypter

		}
	}

}