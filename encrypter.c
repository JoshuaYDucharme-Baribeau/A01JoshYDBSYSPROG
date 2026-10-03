/*encryption logic*/
//encryption logic will require file handling and UI

#include <stdio.h>
#include <string.h>

#include "encrypter.h"

//#include "fileHandler.h"
//#include "userInterface.h"


//stub
int encryptChar(char unencrypted_char, char *term_buffer ) 
{
	int length_indicator = 1;
	int modded_ascii = (unsigned char)unencrypted_char;

	if(modded_ascii == 13 || modded_ascii == 10)
	{
		term_buffer[0] = unencrypted_char;
		term_buffer[1] = '\0';
		length_indicator = 1;
	}
	else if (modded_ascii == 9)
	{
		term_buffer[0] = 'T';
		term_buffer[1] = 'T';
		term_buffer[2] = '\0';
		length_indicator = 2;
	}
	else
	{
		modded_ascii = modded_ascii - 16;
		if (modded_ascii < 32)
		{
			modded_ascii = modded_ascii - 32;
			modded_ascii = modded_ascii + 144;
		}
		length_indicator = 2;
		sprintf(term_buffer, "%02X", modded_ascii);//converts the output to a hex value
	}
	return length_indicator;
	//return "success";
}

//get the ascii code and return 
//int find_ascii(char unencrypted_char) 
//{
//	
//}


//func apply encrypt
	//convert outchar(a decimal int) to hexadecimal