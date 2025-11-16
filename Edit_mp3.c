#include "Tag_Header.h"

const char *Tag_Initials[] = {"-t", "-a", "-A", "-y", "-c", "-m"};
void Edit_Song_Details(char *Tag, char *Edit_Data, char *File_Name)
{
    int i;
    char Edit_Tag[5];
    for (i = 0; i < TAGS_Count; i++)
    {
        if (strcmp(Tag, Tag_Initials[i]) == 0)
        {
            strcpy(Edit_Tag, TAGS[i]);
            break;
        }
    }
    rewind(fptr);   /* To get file pointer back to start.*/
    tptr = fopen("Temp.mp3", "wb");
    if (!tptr)
    {
        perror("Error : ");
        printf("File opening failed!\n");
        exit(1);
    }
    int pos = 0;
    pos = ftell(tptr);
    printf("position %d\n", pos);

    while (1)
    {
        fread(header, 1, 10, fptr);
        fwrite(header, 1, 10, tptr); /* Copy 10 bytes of ID3 header as it is.*/
        size_t Bytes_Read = fread(header, 1, 10, fptr);  /* Read first 10 bytes of Data header.*/
        if (Bytes_Read == 0)    /* To check eof*/
            break;
        // printf("%s\n", TAG_ID);
        if (memcmp(header, Edit_Tag, 4) == 0) /* Check TAG for edit.*/
        {
            printf("Here we are in if.\n");
            fwrite(header, 1, 10, tptr);
            Data_Size = Convert_Size(header + 4);
            printf("sid %s\n", Edit_Data);
            fwrite(Edit_Data, 1, strlen(Edit_Data), tptr);
            fseek(fptr, Data_Size, SEEK_CUR);
            long Remaining_Data = Remaining_Bytes(fptr);
            Tag_Data = malloc(Remaining_Data);
            if (!Tag_Data)
            {
                perror("malloc failed in IF.");
                exit(1);
            }
            size_t Bytes_Read1 = fread(Tag_Data, 1, Remaining_Data, fptr);
            fwrite(Tag_Data, 1, Remaining_Data, tptr);
            if (Bytes_Read1 == 0) /* To check endof file and terminate the while loop.*/
                break;
        }
        else
        {
            printf("Here we are in else.\n");

            fwrite(header, 1, 10, tptr);
            Data_Size = Convert_Size(header + 4);
            Tag_Data = malloc(Data_Size);
            if (!Tag_Data)
            {
                perror("malloc failed in ELSE.");
                exit(1);
            }
            fread(Tag_Data, 1, Data_Size, fptr);
            fwrite(Tag_Data, 1, Data_Size, tptr);
        }
    }

    fclose(tptr);

    /* Remove Sample mp3 file.*/
    if (remove(File_Name) != 0)
    {
        perror("remove failed");
        return;
    }
    /* Rename Temp mp3 file into Sample mp3 file.*/
    if (rename("Temp.mp3", File_Name) != 0)
    {
        perror("renaming failed");
        return;
    }
    printf("Edited successfully!\n");
}

/* Function to get remaining bytes to write as it is in temp.mp3*/
long Remaining_Bytes(FILE *fptr)
{
    long Current_Pos = ftell(fptr);
    fseek(fptr, 0, SEEK_END);
    long End_Pos = ftell(fptr);
    fseek(fptr, Current_Pos, SEEK_SET);
    return End_Pos - Current_Pos;
}