#include "Tag_Header.h"

const char *Tag_Initials[] = {"-t", "-a", "-A", "-y", "-c", "-m"};
void Edit_Song_Details(char *Tag, char *Edit_Data, char *File_Name)
{
    int i;
    char Edit_Tag[5];
    for (i = 0; i < TAGS_Count; i++)
    {
        if (Tag == Tag_Initials[i])
        {
            strcpy(Edit_Tag, TAGS[i]);
        }
    }

    fseek(fptr, 0, SEEK_SET);
    tptr = fopen("Temp.mp3", "wb");
    if (!tptr)
    {
        perror("Error : ");
        printf("File opening failed!\n");
        exit(1);
    }

    fread(header, 1, 10, fptr);
    fwrite(header, 1, 10, tptr);
    fread(header, 1, 10, fptr);

    if (memcmp(header, Edit_Tag, 4) == 0)
    {
        fwrite(header, 1, 10, tptr);
        Data_Size = Convert_Size(header + 4);
        fwrite(Edit_Data, 1, strlen(Edit_Data), tptr);
        fseek(fptr, Data_Size, SEEK_CUR);
        Tag_Data = malloc(Data_Size + 1);
        if (!Tag_Data)
        {
            perror("malloc failed");
            exit(1);
        }
        
    }

    int pos = 0;
    pos = ftell(fptr);
    printf("position %d\n", pos);
}