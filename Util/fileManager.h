#ifndef FILEMANAGER_H
	#define FILEMANAGER_H

	#ifdef __linux__
	    #define DIRECTORY_NAME "./Data/"
	#endif // _WIN32

	#ifdef _WIN32
	    #define DIRECTORY_NAME ".\\Data\\"
	#endif

	#define TRUE 1
	#define FALSE 0

	#define FILE_EXTENSION ".txt"
	#define boolean int
	#define READLINE_BUFFER 16

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>

	boolean openReadFile(char *fileName, FILE *fp);
	boolean openWriteFile(char *fileName, FILE*fp);
	char *readline(FILE *stream);
#endif
