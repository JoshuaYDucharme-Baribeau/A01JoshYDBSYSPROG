//User interface logic
//most src file will call the UI

#include <stdio.h>
#include <string.h>

#include "userInterface.h"

//functions
void displayError(char *errorMessage)
{
	printf("An error occured:\n");
	printf("%s\n", errorMessage);
}
