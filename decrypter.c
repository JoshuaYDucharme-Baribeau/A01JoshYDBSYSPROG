/*
 *	FILE		: decrypter.c
 *	PROJECT		: SENG2031 A01
 *	PROGRAMMER	: Joshua Ducharme-Baribeau
 *	1ST VERSION	: OCT 2, 2026
 *	DESCRIPTION	: Src file which controls decryption logic.
 *
 *
 *
 */

#include <stdio.h>
#include <string.h>

#include "../inc/decrypter.h"


 /*
  *	FUNCTION	: decryptChar
  *	DESCRIPTION	: applies decryption scheme to chars that it is passed
  *
  *
  *	PARAMETERS	: char* encrypted_char	: incoming chars to decrypt
  *				  int pointer_pos		: tracks the position of the index of the incoming characters
  *				  char* output_char		: shadowed name (like many of mine are), pointer to where the decrypted chars are stored
  *
  *	RETURNS		: int chars_decrypted	: amount of chars decrypted, tells the caller how far to advance the file pointer
  */
int decryptChar(char *encrypted_chars, int pointer_pos, char* output_char)
{
	char first_char = encrypted_chars[pointer_pos];
	char second_char = encrypted_chars[pointer_pos + 1];
	
	int chars_decrypted = 2; //amount of chars decrypted, will indicate how far to move the file pointer
	
	//if a tabstop
	if (first_char == 'T' && second_char == 'T')
	{
		output_char[0] = '\t';
		output_char[1] = '\0';

		chars_decrypted = 2;
	}
	//if \n or \r (CR)
	else if(first_char == '\n' || first_char == '\r')
	{
		output_char[0] = first_char;
		output_char[1] = '\0';

		chars_decrypted = 1;
	}
	//if it is a pair of hex digits
	else
	{
		int first_facevalue = 0;
		int second_facevalue = 0;

		//IF FIRST CHAR IS A NUMBER
		if (first_char >= '0' && first_char <= '9')
		{
			first_facevalue = first_char - '0';
		}
		//if first char is a letter
		else
		{
			first_facevalue = first_char - 'A' + 10;
		}


		//IF 2ND CHAR IS A NUMBER
		if (second_char >= '0' && second_char <= '9')
		{
			second_facevalue = second_char - '0';
		}
		//if 2nd char is a letter
		else
		{
			second_facevalue = second_char - 'A' + 10;
		}

		//decryption ensues below
		int real_ascii = (first_facevalue * 16) + second_facevalue;
		real_ascii += 16;

		if (real_ascii > 127)
		{
			real_ascii = (real_ascii - 144) + 32;
		}

		output_char[0] = (char)real_ascii;
		output_char[1] = '\0';

		chars_decrypted = 2;

	}
	return chars_decrypted;
}

