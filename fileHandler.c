/*
 *	FILE		: fileHandler.c
 *	PROJECT		: SENG2031 A01
 *	PROGRAMMER	: Joshua Ducharme-Baribeau
 *	1ST VERSION	: OCT 2, 2026
 *	DESCRIPTION	: Src file which controls any fileHandling required for the program.
 *				  Ideally, this is the only program that opens and closes files.
 *				  This is also what calls for the actual encryption and decryption of chars 
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../inc/fileHandler.h"

#include "../inc/encrypter.h"
#include "../inc/decrypter.h"
#include "../inc/userInterface.h"

//buffer size for any given line (254 + carriage return if any + a potential null terminator for end of file)
#define MAX_LINE_SIZE 256


/*
 *	FUNCTION	: checkFileExistence
 *	DESCRIPTION	: func to check that the file passed as an argument exists
 *
 *
 *	PARAMETERS	: char* fileName: name of the file to find
 *				  
 *
 *
 *	RETURNS		: bool existence: indicates if file exists (true) or not (false)
 */
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

/*
 *	FUNCTION	: readFile
 *	DESCRIPTION	: func to read the file that user wants to encrypt or decrypt
 *		it also calls the appropriate functions to decrypt, decrypt, 
 *		and write the resulting data to a file
 * 
 *	PARAMETERS	: char* fileName: name of the file to encrypt or decrypt
 *				  int crypto_mode: determines flag to indicate decryption or encryption
 *
 *	RETURNS		: char* outChar: the encrypted or decrypted data
 */
char* readFile(char *fileName, int crypto_mode) 
{
	FILE* p_file = fopen(fileName, "r");
	if (!p_file) 
	{
		displayError("Error opening file.\n");
		return NULL;
	}

	// Determine the file size by finding the end and setting the length to the filepointer's index
	fseek(p_file, 0, SEEK_END);
	long file_size = ftell(p_file);
	rewind(p_file);//brings the file pointer back to the start

	//holds the encrypted text, which is the size of the file times 2
	char* outChar = malloc(file_size * 2 + 1); //allocate double the amount of chars plus the null temrinator
	if (!outChar)
	{
		fclose(p_file);
		displayError("Failed to allocate memory.\n");
		return NULL;
	}


	char line[MAX_LINE_SIZE] = {0}; 
	long index_of_outChar = 0;
	char term_buffer[4]; //a buffer large enough to hold up to 3 characters and a null terminator (2 encrypted characters and a null term+ 1 for safety and to round up to 4)
	

	while(fgets(line, sizeof(line), p_file) != NULL)
	{
		if(crypto_mode == 1) //encryption mode
		{
			for (int i = 0; line[i] != '\0'; i++)  //iterate by line until line terminator
			{
				int enc_output_length = encryptChar(line[i], term_buffer); //amount of characters returned by the encrypter

				//this loop allows the encrypted characters to be stored, regardless if there are 2 characters (a hex value or TT) or only a CR (/n or /r)
				for (int j = 0; j < enc_output_length; j++)			//iterate by character returned by the encrypter (up to 4 technically, but usually 1 for a /n or 2 for a regular char)
				{
					outChar[index_of_outChar++] = term_buffer[j];	//save the character in the buffer
				}

			}
		}
		//otherwise decryption mode:
		else
		{
			for (int i = 0; line[i] != '\0';) //iterate by line until line terminator
			{
				int chars_decrypted = decryptChar(line, i, term_buffer); //amount of characters returned by the encrypter, should always be 1

				outChar[index_of_outChar++] = term_buffer[0]; //save the character in the buffer

				//move the pointer of the file reader by the amount of chars decrypted, which should typically be 1
				i += chars_decrypted;
			}
		}

	}

	outChar[index_of_outChar] = '\0'; //ends the string of encrypted characters with a null terminator
	fclose(p_file);
	return outChar;
}


/*
 *	FUNCTION	: writeEncryption
 *	DESCRIPTION	: writes already encrypted data to a file
 *		
 *		
 *
 *	PARAMETERS	: char* fileName: name of the file that was submitted for encryption, used to generate a new filename
 *				  char* outChar: the encrypted data to write to a file
 *
 *	RETURNS		: void : NOTHING
 */
void writeEncryption(char* fileName, char* outChar) 
{
	//get the name of the file to be/modded
	char *output_name = newFileName(fileName);

	FILE* p_file = fopen(output_name, "w");
	if (!p_file)
	{
		displayError("Error opening file.\n");
		return;
	}
	//actually print the saved encrypted or decrypted characters to the new or overwritten file
	fputs(outChar, p_file);

	free(output_name);
	fclose(p_file);
	return;
}


/*
 *	FUNCTION	: newFileName
 *	DESCRIPTION	: create a suitable name for the new encrypted file
 *
 *
 *
 *	PARAMETERS	: char* fileName: name of the file that was submitted for encryption, used to generate a new filename
 *				  
 *
 *	RETURNS		: void : NOTHING
 */
char* newFileName(char* fileName) 
{
	//find the length of the parameter file name, 
	size_t name_length = strlen(fileName);
	//and find the fist instance of a '.' from REVERSE ORDER
	char* period = strrchr(fileName, '.');

	//If there's no '.', just add .crp to the end (includes memalloc for null term)
	if (!period)
	{
		char* output_name = malloc(name_length + 5);
		if (!output_name)
		{
			displayError("error allocating memory for outputname");
			return NULL;
		}
		strcpy(output_name, fileName);
		strcat(output_name, ".crp");
		return output_name;
	}
	//if there is a file ext
	else
	{
		//get the name size without the extension
		size_t len_without_ext = period - fileName;

		//allocate for the new .crp extension
		char* output_name = malloc(len_without_ext + 5);
		if (!output_name)
		{
			displayError("error allocating memory for outputname");
			return NULL;
		}

		strncpy(output_name, fileName, len_without_ext);
		//remove the existing extension
		output_name[len_without_ext] = '\0';
		//add .crp
		strcat(output_name, ".crp");

		return output_name;
	}

}


/*
 *	FUNCTION	: writeDecrypted
 *	DESCRIPTION	: writes already Decrypted data to a file
 *
 *
 *
 *	PARAMETERS	: char* fileName: name of the file that was submitted for decryption, used to generate a new filename
 *				  char* outChar: the decrypted data to write to a file
 *
 *	RETURNS		: void : NOTHING
 */
void writeDecrypted(char* fileName, char* outChar)
{
	//get the name of the file to be/modded
	char* output_name = newDecryptedFileName(fileName);
	
	FILE* p_file = fopen(output_name, "w");
	if (!p_file)
	{
		displayError("error when writing the decrypted data to a file.");
		free(output_name);
		return;
	}

	//write the data to the new decrypted file
	fputs(outChar, p_file);

	fclose(p_file);
	free(output_name);

}


/*
 *	FUNCTION	: newDecryptedFileName
 *	DESCRIPTION	: create a suitable name for the new decrypted file
 *				  Assumes decryption will always run on a .crp and output a .txt, as per instructions
 *
 *
 *	PARAMETERS	: char* fileName: name of the file that was submitted for decryption, used to generate a new filename
 *
 *
 *	RETURNS		: void : NOTHING
 */
char* newDecryptedFileName(char* fileName)
{

	//find the fist instance of a '.' from REVERSE ORDER
	char* period = strrchr(fileName, '.');
	size_t len_without_ext;
	
	//if there's an extension and it is .crp
	if (period && strcmp(period, ".crp") == 0)
	{
		len_without_ext = period - fileName;
	}
	else 
	{
		len_without_ext = strlen(fileName);
	}

	char* output_name = malloc(len_without_ext + 5); //allocate for the new .txt extension
	if (!output_name)
	{
		displayError("error allocating memory for the name of the decrypted file");
		return NULL;
	}

	strncpy(output_name, fileName, len_without_ext);
	//remove the existing extension
	output_name[len_without_ext] = '\0';
	//add .txt
	strcat(output_name, ".txt");
	return output_name;
}

