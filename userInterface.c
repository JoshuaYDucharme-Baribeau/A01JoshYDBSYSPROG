/*
 *	FILE		: userInterface.c
 *	PROJECT		: SENG2031 A01
 *	PROGRAMMER	: Joshua Ducharme-Baribeau
 *	1ST VERSION	: OCT 2, 2026
 *	DESCRIPTION	: Src file which has a function to display errors to the console/terminal
 *
 *
 *
 */

#include <stdio.h>
#include <string.h>

#include "../inc/userInterface.h"

 /*
  *	FUNCTION	: displayError
  *	DESCRIPTION	: displays an error to the console based on the message it is passed
  *
  *
  *	PARAMETERS	: char* errorMessage	: a meaningful message about the error that occured
  *
  *
  *
  *	RETURNS		: void	: NOTHING
  */
void displayError(char *errorMessage)
{
	printf("An error occured:\n");
	printf("%s\n", errorMessage);
}
