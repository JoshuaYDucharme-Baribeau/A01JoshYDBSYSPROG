/*file Handling logic*/
//The file handler shouldn't be calling much else other than UI for confirmations (subject to change)

#include <stdio.h>
#include <string.h>

#include "fileHandler.h"

//#include "encrypter.h"
//#include "decrypter.h"
#include "userInterface.h"

//check that file exists
bool checkFileExistence(char[] fileName)
{
	bool existence = NULL;
	FILE* p_file = NULL;

	p_file = fopen(fileName, "r");
	if(p_file == NULL) 
	{
		existence = false;
	}
	else
	{
		existence = true;
	}
	return existence;
}