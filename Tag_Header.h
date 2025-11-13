#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE *fptr;

/* Array of string tags.*/
extern const char *TAGS[];
extern const int TAGS_Count;

/* Function Prototypes.*/
void View_Song_Details(char *File_Name);
unsigned int Convert_Size(const unsigned char size_bytes[4]);