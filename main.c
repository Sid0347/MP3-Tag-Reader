#include "Tag_Header.h"

FILE *fptr = NULL;
FILE *tptr = NULL;

int main(int argc, char *argv[])
{
    /* Error and usage message if argument is equal or less than one.*/
    if (argc <= 1)
    {
        error_and_usage();
        return 1;
    }
    /* The help menu (Show detailed meaning of argument.)*/
    if (strcmp(argv[1], "--help") == 0)
    {
        help_menu();
        return 1;
    }

    /* Check for to get correct position of file name from command line argument.*/
    int argv_num;
    if (strcmp(argv[1], "-v") == 0)
    argv_num = 2;   /*If true -> Second index argument is file name.*/
    else
    argv_num = 4;   /*If false -> forth index argument is file name.*/

    /* Check for '.mp3' extension.*/
    if (strstr(argv[argv_num], ".mp3") == NULL)
    {
        printf("Error : File extension not match!\n");
        return 0;
    }
    /* Open file in read mode.*/
    fptr = fopen(argv[argv_num], "rb");
    if (!fptr)
    {
        perror("Error : ");
        printf("File opening failed!\n");
        exit(1);
    }
    /* Check for ID3 tag.*/
    char TAG_ID[4];
    fread(TAG_ID, 1, 3, fptr);
    TAG_ID[3] = '\0';
    if (strcmp(TAG_ID, "ID3") != 0)
    {
        printf("Error : ID3 tag not found, cannot read MP3 metadata.\n");
        return 0;
    }
    /* Check for Version(03 00).*/
    char version[2];
    fread(version, 1, 2, fptr);
    if (memcmp(version, "\x03\x00", 2) != 0)
    {
        printf("Error : Unsupported ID3 version, only ID3v2.3 and ID3v2.4 are supported.\n");
        return 0;
    }
    
    fseek(fptr, 5, SEEK_CUR);   /* Skip remaining header bytes.*/
    
    /* Check for first index whether it is for view or edit.*/
    if (strcmp(argv[1], "-v") == 0)
    {
        view_song_details(argv[2]);
    }
    
    if (strcmp(argv[1], "-e") == 0)
    {
        edit_song_details(argv[2], argv[3], argv[4]);
    }
    
    fclose(fptr);

    return 0;
}
