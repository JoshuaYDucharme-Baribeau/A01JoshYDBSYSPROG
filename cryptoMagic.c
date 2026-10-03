/*
Main SRC file for A1
Joshua Ducharme-Baribeau
*/

#include <stdio.h>
#include <string.h>

//#include "cryptoMagic.h"

#include "run.h"
#include "userInterface.h"

//main only calls the run function
int main(int argc, char *argv[])
{
	//if there are two arguments (including command), i.e. only a file name as an additional argument
	if (argc == 2)
	{
		run("-encrypt", argv[1]);
	}
	//if there are 3 arguments and the 2nd argument is -encrypt or -decrypt
	else if ((argc == 3) && (strcmp(argv[1], "-encrypt") == 0 || strcmp(argv[1], "-decrypt") == 0))
	{
		run(argv[1], argv[2]);
	}
	//too many arguments or insufficient arguments
	else
	{
		//display an error message using the interface //Note, consider using a variable to hold this long char array
		displayError("Incorrect use of cryptoMagic. Please use the command as follows:\nTo encrypt:\"cryptoMagic -encrypt fileToEncrypt.txt\" or \"cryptoMagic fileToEncrypt.txt\" \nTo decrypt:\"cryptoMagic -decrypt fileToDecrypt.crp\"");
	}

	return(0);
}
