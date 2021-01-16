#include <stdio.h>
#include<string.h>

int main(int argc, char *argv[])
{
    int flag = 0;  //for no flag
    int flag2 = 0; // for -i
    int flag3 = 0; //for -d
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-i") == 0)
        {
            flag2 = 1;
        }
        if (strcmp(argv[i], "-d") == 0)
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
            int status = remove(argv[i]);
            if (status !=0)
            {
                printf("cannot remove %s: Is a directory\n",argv[i]);
            }
        }
    }
    if (flag2 == 1)
    {
        for (int i = 2; i < argc; i++)
        {
            char check;
            printf("rm: remove regular file %s?", argv[i]);
            scanf("%c", &check);
            if (check == 'y')
            {
                int status = remove(argv[i]);
                if (status !=0)
                {
                    printf("cannot remove %s: Is a directory\n",argv[i]);
                }
            }
        }
    }
    if (flag3 == 1)
    {
        for (int i = 2; i < argc; i++)
        {
            int status = remove(argv[i]);
            if (status != 0)
            {
                printf("failed to remove 'new': Directory not empty   \n");
            }
        }
    }

    return 0;
}