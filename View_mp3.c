#include "Tag_Header.h"

/* Tags to check readed tag are correct or not*/
const char *TAGS[] = {"TIT2", "TPE1", "TALB", "TYER", "TCON", "COMM"};
const char *Lables[] = {"Title       :   ", "Artist      :   ", "Album       :   ", "Year        :   ", "Content     :   ", "Comment     :   "};
unsigned int Data_Size;
unsigned char *Tag_Data;
unsigned char header[10];

void View_Song_Details(char *File_Name)
{
    printf("|-------------------SELECTED VIEW DETAILS--------------------|\n");
    printf("|------------------------------------------------------------|\n");
    printf("            MP3 TAG READER AND EDITOR FOR ID3v2               \n");
    printf("|------------------------------------------------------------|\n");
    int i = 0;
    while (i != TAGS_Count) /* while loop terminate when i = 6.*/
    {
        fread(header, 1, 10, fptr);
        Data_Size = Convert_Size(header + 4);
        Tag_Data = malloc(Data_Size + 1);
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
    }
    printf("|------------------------------------------------------------|\n");
}

/* Function to convert 4-byte big-endian value from file into little-endian.*/
unsigned int Convert_Size(const unsigned char size_bytes[4])
{
    return (size_bytes[0] << 24) | (size_bytes[1] << 16) | (size_bytes[2] << 8) | size_bytes[3];
}