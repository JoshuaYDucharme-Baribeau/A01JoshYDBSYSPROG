/*
 *	FILE		: cryptoMagic.c
 *	PROJECT		: SENG2031 A01
 *	PROGRAMMER	: Joshua Ducharme-Baribeau
 *	1ST VERSION	: OCT 2, 2026
 *	DESCRIPTION	: Src containing Main entry point for A1,
 *				  only calls run and displayerror funcs
 * 
 * 
 */



#include <stdio.h>
#include <string.h>

//this header file didn't end up being needed
//#include "cryptoMagic.h"

#include "../inc/run.h"
#include "../inc/userInterface.h"

//main only calls the run function and can display an error
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
	//too many arguments, insufficient arguments, or incorrect arguments
	else
	{
		//display an error message using the interface //Note, consider using a variable to hold this long char array
		displayError("Incorrect use of cryptoMagic. Please use the command as follows:\nTo encrypt: \"cryptoMagic -encrypt fileToEncrypt.txt\" or \"cryptoMagic fileToEncrypt.txt\" \nTo decrypt: \"cryptoMagic -decrypt fileToDecrypt.crp\"\n");
	}

	return(0);
}
