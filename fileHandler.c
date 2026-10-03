/*file Handling logic*/
//The file handler shouldn't be calling much else other than UI for confirmations (subject to change)

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "fileHandler.h"

//#include "encrypter.h"
//#include "decrypter.h"
#include "userInterface.h"

//check that file exists
bool checkFileExistence(char *fileName)
{
	bool existence = false;
	FILE* p_file = fopen(fileName, "r"); 

	if(p_file == NULL)
	{
		existence = false;
	}
	else
	{
		fclose(p_file);
		existence = true;
		
	}

	return existence;
}

//function to remove the file extension if any and replace it with the correct extension as required

//function to write the new encrypted or decrypted file