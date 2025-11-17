#include "Tag_Header.h"

/* Tags to check readed tag are correct or not*/
const char *TAGS[] = {"TIT2", "TPE1", "TALB", "TYER", "TCON", "COMM"};
const char *Lables[] = {"Title       :   ", "Artist      :   ", "Album       :   ", "Year        :   ", "Content     :   ", "Comment     :   "};
uint32_t Data_Size;
unsigned char *Tag_Data;
unsigned char header[10];

void view_song_details(char *File_Name)
{
    printf("|-------------------SELECTED VIEW DETAILS--------------------|\n");
    printf("|------------------------------------------------------------|\n");
    printf("            MP3 TAG READER AND EDITOR FOR ID3v2               \n");
    printf("|------------------------------------------------------------|\n");
    int i = 0;
    while (i != TAGS_Count) /* while loop terminate when i = 6.*/
    {
        if (fread(header, 1, 10, fptr) != 10) /* Stop if header reach EOF or read is corrupt.*/
            break;

        Data_Size = convert_little(header + 4);
        if (Data_Size == 0) /* If data size comes zero then avoid malloc(0).*/
            break;
        Tag_Data = malloc(Data_Size);
        if (!Tag_Data)
        {
            perror("malloc failed in View");
            exit(1);
        }

        if (fread(Tag_Data, 1, Data_Size, fptr) != Data_Size) /* Stop if data not fully read.*/
        {
            free(Tag_Data);
            break;
        }

        /* Check for tag*/
        for (int j = 0; j < TAGS_Count; j++)
        {
            if (memcmp(header, TAGS[j], 4) == 0)
            {
                printf("%s", Lables[j]);
                fwrite(Tag_Data, 1, Data_Size, stdout);
                printf("\n");

                if (j == i)
                    i++;
                break;
            }
        }
        free(Tag_Data);
    }
    printf("|------------------------------------------------------------|\n");
}

/* Error and usage message if argument is equal or less than one.*/
void error_and_usage()
{
    printf("------------------------------------------------------------------------------------------\n");
    printf("ERROR : ./a.out : INVALID ARGUMENTS\n");
    printf("To view please pass like : ./a.out -v mp3filename\n");
    printf("To edit please pass like : ./a.out -e (-t/ -a/ -A/ -m/ -y/ -c) changing_text mp3filename\n");
    printf("To get help pass like : ./a.out --help\n");
    printf("------------------------------------------------------------------------------------------\n");
}

/* The help menu (Show detailed meaning of argument.)*/
void help_menu()
{
    printf("--------------------HELP MENU--------------------\n");
    printf("1. -v -> To view mp3 file contents\n2. -e -> To edit mp3 file contents\n");
    printf("    2.1] -t -> To edit song title\n");
    printf("    2.2] -a -> To edit artist name\n");
    printf("    2.3] -A -> To edit album name\n");
    printf("    2.4] -y -> To edit year\n");
    printf("    2.5] -c -> To edit content\n");
    printf("    2.6] -m -> To edit comment\n");
    printf("-------------------------------------------------\n");
}