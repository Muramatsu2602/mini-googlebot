#include "fileManager.h"

boolean openReadFile(char *fileName, FILE *fp)
{
	fp = fopen(fileName,"r");
	if (fp!=NULL)
	{
		return TRUE;
	}
	
	return FALSE;
}

boolean openWriteFile(char *fileName, FILE *fp)
{
	fp = fopen(fileName,"w");
	if (fp!=NULL)
	{
		return TRUE;
	}
	
	return FALSE;
}

// You can read file lines using this function
char *readline(FILE *stream)
{
	char *string = NULL;
	int pont = 0;
	do
	{
		if (pont % READLINE_BUFFER == 0)
		{
			string = (char *)realloc(string, ((pont / READLINE_BUFFER) + 1) * READLINE_BUFFER);
		}
		string[pont] = (char)fgetc(stream);
	} while (string[pont++] != '\n' && !feof(stream));
	string[pont - 1] = '\0';
	return string;
}