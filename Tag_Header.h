#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define TAGS_Count 6

extern FILE *fptr;
extern FILE *tptr;

/* Array of string tags.*/
extern const char *TAGS[];
extern unsigned char header[];
extern unsigned int Data_Size;
extern unsigned char *Tag_Data;

/* Function Prototypes.*/
void error_and_usage();
void help_menu();
void view_song_details(char *File_Name);
void edit_song_details(char *Tag, char *Edit_Data, char *File_Name);
uint32_t convert_little(const unsigned char size_bytes[4]);
uint32_t to_big_endian(uint32_t Edit_Size, unsigned char Edit_Bytes[4]);
long remaining_bytes(FILE *fptr);