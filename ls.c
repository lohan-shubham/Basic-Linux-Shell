/**
 * C program to list all files and sub-directories in a directory.
 */

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

int main(char *argc, char *argv[])
{
    char path[100];
    int flag = 0;
    // printf("%d\n", argc);
    getcwd(path, sizeof(path));
    struct dirent *dp;
    DIR *dir = opendir(path);
    // Unable to open directory stream
    if (!dir)
        return 0;
    if (argv[1]==NULL)
    {
        while ((dp = readdir(dir)) != NULL)
        {
            if (dp->d_name[0] != '.')
                printf("%s  ", dp->d_name);
        }
    }
    else if (strcmp(argv[1], "-a") == 0)
    {
        while ((dp = readdir(dir)) != NULL)
        {
                printf("%s  ", dp->d_name);
        }
    }
    else if (strcmp(argv[1], "-m") == 0)
    {
        while ((dp = readdir(dir)) != NULL)
        {
            if (dp->d_name[0] != '.')
                printf("%s,  ", dp->d_name);
        }
    }
    printf("\n");
    // Close directory stream
    closedir(dir);
    

    return 0;
}
