/*
 *	FILE		: encrypter.c
 *	PROJECT		: SENG2031 A01
 *	PROGRAMMER	: Joshua Ducharme-Baribeau
 *	1ST VERSION	: OCT 2, 2026
 *	DESCRIPTION	: Src file which controls encryption logic.
 *				  
 *				  
 *
 */

#include <stdio.h>
#include <string.h>

#include "../inc/encrypter.h"



 /*
  *	FUNCTION	: encryptChar
  *	DESCRIPTION	: applies encryption scheme to chars that it is passed
  *	
  *	
  *
  *	PARAMETERS	: char unencrypted_char	: incoming char to encrypt
  *				  char* term_buffer		: the char pointer to the buffer where the encrypted chars will be stored
  *
  *	RETURNS		: int length_indicator	: amount of chars encrypted, tells the caller how far to advance the file pointer
  */
int encryptChar(char unencrypted_char, char *term_buffer) 
{
	
	int length_indicator = 0; //amount of chars returned encrypted, tells the caller how far to advance the file pointer
	int modded_ascii = (unsigned char)unencrypted_char;

	//if the char is /r or /n
	if(modded_ascii == 13 || modded_ascii == 10)
	{
		term_buffer[0] = unencrypted_char;
		term_buffer[1] = '\0';
		length_indicator = 1; //only move the file pointer by 1 char on return
	}
	//if the char is a Tab
	else if (modded_ascii == 9)
	{
		//always encrypt with two 'T's
		term_buffer[0] = 'T';
		term_buffer[1] = 'T';
		term_buffer[2] = '\0';
		length_indicator = 2; //move filepointer by 2 chars on return
	}
	//all other chars folllow this encryption scheme
	else
	{
		modded_ascii = modded_ascii - 16;
		if (modded_ascii < 32)
		{
			modded_ascii = modded_ascii - 32;
			modded_ascii = modded_ascii + 144;
		}
		length_indicator = 2; //move filepointer by 2 chars on return
		sprintf(term_buffer, "%02X", modded_ascii);//converts the output to a hex value with 2 significant values and storeds them in the term_buffer
	}
	return length_indicator;
}
