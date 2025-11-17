#include "Tag_Header.h"

const char *Tag_Initials[] = {"-t", "-a", "-A", "-y", "-c", "-m"};
void edit_song_details(char *Tag, char *Edit_Data, char *File_Name)
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
    rewind(fptr); /* To get file pointer back to start.*/
    tptr = fopen("Temp.mp3", "wb");
    if (!tptr)
    {
        perror("Error : ");
        printf("File opening failed!\n");
        exit(1);
    }

    fread(header, 1, 10, fptr);
    fwrite(header, 1, 10, tptr); /* Copy 10 bytes of ID3 header as it is.*/
    unsigned char Edit_Bytes[4];
    while (1)
    {
        size_t Bytes_Read = fread(header, 1, 10, fptr); /* Read first 10 bytes of Data header.*/
        if (Bytes_Read == 0)                            /* To check eof*/
            break;

        Data_Size = convert_little(header + 4);

        // printf("%s\n", TAG_ID);
        if (memcmp(header, Edit_Tag, 4) == 0) /* Check TAG for edit.*/
        {
            fwrite(header, 1, 4, tptr);
            to_big_endian(strlen(Edit_Data), Edit_Bytes);
            fwrite(Edit_Bytes, 1, 4, tptr);
            fwrite(&header[8], 1, 2, tptr);
            fwrite(Edit_Data, 1, strlen(Edit_Data), tptr);
            fseek(fptr, Data_Size, SEEK_CUR);
            long Remaining_Data = remaining_bytes(fptr);
            if (Remaining_Data > 0)
            {
                Tag_Data = malloc(Remaining_Data);
                if (!Tag_Data)
                {
                    perror("malloc failed in IF.");
                    exit(1);
                }

                fread(Tag_Data, 1, Remaining_Data, fptr);
                fwrite(Tag_Data, 1, Remaining_Data, tptr);
                free(Tag_Data);
            }
            break;
        }
        else
        {
            fwrite(header, 1, 10, tptr);
            Tag_Data = malloc(Data_Size);
            if (!Tag_Data)
            {
                perror("malloc failed in ELSE.");
                exit(1);
            }
            fread(Tag_Data, 1, Data_Size, fptr);
            fwrite(Tag_Data, 1, Data_Size, tptr);
            free(Tag_Data);
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
long remaining_bytes(FILE *fptr)
{
    long Current_Pos = ftell(fptr);
    fseek(fptr, 0, SEEK_END);
    long End_Pos = ftell(fptr);
    fseek(fptr, Current_Pos, SEEK_SET);
    return End_Pos - Current_Pos;
}

/* Function to convert 4-byte big-endian value from file into little-endian.*/
uint32_t convert_little(const unsigned char size_bytes[4])
{
    return (size_bytes[0] << 24) | (size_bytes[1] << 16) | (size_bytes[2] << 8) | size_bytes[3];
}

uint32_t to_big_endian(uint32_t Edit_Size, unsigned char Edit_Bytes[4])
{
    Edit_Bytes[0] = (Edit_Size >> 24) & 0xFF;
    Edit_Bytes[1] = (Edit_Size >> 16) & 0xFF;
    Edit_Bytes[2] = (Edit_Size >> 8) & 0xFF;
    Edit_Bytes[3] = Edit_Size & 0xFF;
}
