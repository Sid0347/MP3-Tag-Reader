#include "Tag_Header.h"

/* Tags to check readed tag are correct or not*/
const char *TAGS[] = {"TIT2", "TPE1", "TALB", "TYER", "TCON", "COMM"};
const char *Lables[] = {"Title       :   ", "Artist      :   ", "Album       :   ", "Year        :   ", "Content     :   ", "Comment     :   "};
const int TAGS_Count = 6;
int i;
int Temp_Count; /* For while loop termination.*/

unsigned char header[10];
void View_Song_Details(char *File_Name)
{
    printf("|-------------------SELECTED VIEW DETAILS--------------------|\n");
    printf("|------------------------------------------------------------|\n");
    printf("            MP3 TAG READER AND EDITOR FOR ID3v2               \n");
    printf("|------------------------------------------------------------|\n");
    while (Temp_Count != TAGS_Count)
    {
        fread(header, 1, 10, fptr);
        unsigned int Data_Size = Convert_Size(header + 4);
        unsigned char *Tag_Data = malloc(Data_Size + 1);
        if (!Tag_Data)
        {
            perror("malloc failed");
            exit(1);
        }
        fread(Tag_Data, 1, Data_Size, fptr);

        /* Check for tag*/
        if (memcmp(header, TAGS[i], 4) == 0)
        {
            printf("%s", Lables[i]);
            fwrite(Tag_Data, 1, Data_Size, stdout);
            printf("\n");
            i++;
        }
        Temp_Count++;
    }
    printf("|------------------------------------------------------------|\n");
    
}

/* Function to convert 4-byte big-endian value from file into little-endian.*/
unsigned int Convert_Size(const unsigned char size_bytes[4])
{
    return (size_bytes[0] << 24) | (size_bytes[1] << 16) | (size_bytes[2] << 8) | size_bytes[3];
}