#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAGS_Count 6

extern FILE *fptr;
extern FILE *tptr;

/* Array of string tags.*/
extern const char *TAGS[];
extern unsigned char header[];
extern unsigned int Data_Size;
extern unsigned char *Tag_Data;

/* Function Prototypes.*/
void View_Song_Details(char *File_Name);
void Edit_Song_Details(char *Tag, char *Edit_Data, char *File_Name);
unsigned int Convert_Size(const unsigned char size_bytes[4]);
long Remaining_Bytes(FILE *fptr);