/*file Handling logic*/
//The file handler shouldn't be calling much else other than UI for confirmations (subject to change)

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "fileHandler.h"

#include "encrypter.h"
//#include "decrypter.h"
#include "userInterface.h"

#define MAX_LINE_SIZE 256

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

//open and read a file for encryption
char* readForEncryption(char *fileName) 
{
	FILE* p_file = fopen(fileName, "r");
	if (!p_file) 
	{
		displayError("Error opening file.\n");
		return NULL;
	}

	// Determine the file size
	fseek(p_file, 0, SEEK_END);
	long file_size = ftell(p_file);
	rewind(p_file);//brings the file pointer back to the start

	//holds the encrypted text, which is the size of the file times 2
	char* outChar = malloc(file_size * 2 + 1); //allocate double chars plus the null temrinator
	if (!outChar)
	{
		fclose(p_file);
		displayError("Failed to allocate memory.\n");
		return NULL;
	}


	//outChar[0] = '\0'; //inistialize the char array as empty

	char line[MAX_LINE_SIZE] = {0};
	long index_of_outChar = 0;
	char term_buffer[4]; //a buffer large enough to hold up to 3 characters and a null terminator
	

	while(fgets(line, sizeof(line), p_file) != NULL)
	{

		for(int i = 0; line[i] != '\0'; i++)
		{
			int enc_output_length = encryptChar(line[i], term_buffer);
			
			//this loop allows the encrypted characters to be stored, regardless if there are 2 characters (a hex value or TT) or only a CR (/n or /r)
			for (int j = 0; j < enc_output_length; j++)
			{
				outChar[index_of_outChar++] = term_buffer[j];
			}

		}
		
	}

	outChar[index_of_outChar] = '\0'; //ends the string of encrypted characters with a null terminator
	fclose(p_file);
	return outChar;
}

//write to an encrypted file

void writeEncryption(char* fileName, char* outChar) 
{
	char *output_name = newFileName(fileName);
	FILE* p_file = fopen(output_name, "w");
	if (!p_file)
	{
		displayError("Error opening file.\n");
		return;
	}
	fputs(outChar, p_file);

	free(output_name);
	fclose(p_file);
}

char* newFileName(char* fileName) 
{
	size_t name_length = strlen(fileName);
	char* period = strrchr(fileName, '.');

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
	else
	{
		size_t len_without_ext = period - fileName;

		char* output_name = malloc(len_without_ext + 5);
		if (!output_name)
		{
			displayError("error allocating memory for outputname");
			return NULL;
		}

		strncpy(output_name, fileName, len_without_ext);
		output_name[len_without_ext] = '\0';

		strcat(output_name, ".crp");
		return output_name;

	}

}


		//get ascii code from char
		//if ascii 9 
			// then output "TT"
		//else if ascii is a carriage return
			// don't modify and skip to the next line (continue)
		//else
			// ascii - 16
			//if ((ascii) < 32)
				// ascii - 32
				// ascii + 144
			//no else
			// 
		// func apply encryption to the number
		// 

//function to remove the file extension if any and replace it with the correct extension as required

//function to write the new encrypted or decrypted file