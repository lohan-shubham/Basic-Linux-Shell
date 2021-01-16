
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
int main(char argc, char *argv[])
{
    int flag = 0;  //for no flag
    int flag2 = 0; // for -p no warning
    int flag3 = 0; //for --help
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-p") == 0)
        {
            flag2 = 1;
        }
        if (strcmp(argv[i], "--help") == 0)
        {
            flag3 = 1;
        }
    }
    if (flag2 == 1 && flag3 == 1)
    {
        printf("Enter right command\n");
        return 0;
    }
    if (flag2 == 0 && flag3 == 0)
    {
        flag = 1;
    }

    if (flag == 1)
    {
        for (int i = 1; i < argc; i++)
        {
            int check = mkdir(argv[i], 0777);
            //checking if directory is created
            if (check!=0)
                printf(" cannot create directory %s: File exists \n", argv[i]);
        }
    }

    if (flag2 == 1)
    {
        for (int i = 1; i < argc; i++)
        {
            int check = mkdir(argv[i], 0777);
        }
    }
    //    system("dir/p");
    if(flag3==1){
        printf("Usage: mkdir [OPTION]... DIRECTORY...\nCreate the DIRECTORY(ies), if they do not already exist.\nMandatory arguments to long options are mandatory for short options too.\n -p, --parents     no error if existing, make parent directories as needed \n--help     display this help\n");
    }
}
