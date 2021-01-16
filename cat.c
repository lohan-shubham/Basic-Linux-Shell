#include <stdio.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define clear() printf("\033[H\033[J")
/* cat: concatenate files - read/write/open/close */

int main(int argc, char *argv[])
{
    // clear();
    // printf("%d \n", argc);
    // printf("inside cat\n");
    int cat_flag = 0; // 0 for no flag 1 for -n ,2 for -E
    int cat_flag2 = 0, cat_flag3 = 0;


    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-n") == 0)
        {
            cat_flag2 = 1;
        }
        if (strcmp(argv[i], "-E") == 0)
        {
            cat_flag3 = 1;
        }
    }
    if (cat_flag2 == 1 && cat_flag3 == 1)
    {
        printf("Enter right command\n");
        return 0;
    }
    if(cat_flag2==0 && cat_flag3==0){
        cat_flag=1;
    }
    FILE *file;
    // for (int i=0; i<10; i++)
    //      file[i] = (FILE *)malloc(100* sizeof(FILE));
    int i = 1;
    if (cat_flag2 || cat_flag3)
    {
        i = 2;
    }
    for (; i < argc; i++)
    {
        file = fopen(argv[i], "r");

        if (file == NULL)
        {
            printf("file no such file\n");
            break;
        }

            if (cat_flag == 1)
            {
                char filedata[100];
                while (fgets(filedata, 100, file) != NULL)
                {

                    printf("%s", filedata);
                    // write(1, filedata, strlen(filedata));
                }
                fclose(file);
            }

            if (cat_flag2 == 1)
            {
                char filedata[100];
                int counter = 1;
                while (fgets(filedata, 100, file) != NULL)
                {

                    printf("%d %s", counter++, filedata);
                }
                fclose(file);
            }
            if (cat_flag3 == 1)
            {
                char filedata[100];
                int counter = 1;
                while (fgets(filedata, 100, file) != NULL)
                {

                    printf("%s", filedata);
                }
                printf("$");
                fclose(file);
            }
        
    }
    return 0;
}