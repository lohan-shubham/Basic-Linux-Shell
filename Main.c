#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
char commandPath[100];
char history_path[100] = {"/home/"};
#define clear() printf("\033[H\033[J")
pid_t pid;
char int_command[5][200] = {"cd", "echo", "history", "pwd", "exit"};
char ext_command[5][200] = {"ls", "cat", "date", "rm", "mkdir"};
void performInternal(char *);
void performExternal(char *);
char *username;

void printHistory(char flag[])
{
    if (strcmp(flag, "-c") == 0 || strcmp(flag,"-w")==0) // to remove all history
    {
        char h_cmd[100]={"cd /home/"};
        strcat(h_cmd,username);
        strcat(h_cmd,"&& rm .bash_history");
        // performInternal("cd /home/shubham-lohan/");
        // performExternal("rm .bash_history");
        system(h_cmd);

        return;
    }
    FILE *file;
    char display[100];
    file = fopen(history_path, "a+");
    int counter = 1;
    while (fgets(display, 100, file) != NULL)
    {
        printf("%d  %s\n", counter++, display);
    }
    fclose(file);
}
void runecho(char flag[], char *word)
{
    if (strcmp(flag, "-n") == 0)
    {
        while (word != NULL)
        {
            printf("%s", word);
            word = strtok(NULL, " ");
        }
        return;
    }
    while (word != NULL)
    {
        // printf("outside: %s\n", word);
        word = strtok(NULL, " ");
    }
}
int checkcommand(char command[])
{
    for (int i = 0; i < 5; i++)
    {
        if (strcmp(command, int_command[i]) == 0)
        {
            return 0;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        if (strcmp(command, ext_command[i]) == 0)
        {
            return 1;
        }
    }
    return -1;
}
void runDate(char *command)
{
    // char *const argv[]={"./date","-u",NULL};
    int index = 0;
    char *temp = command;
    int flag = 0;
    int flag_u = 0;
    int flag_r = 0;
    int counter = 0;
    char path[100];
    strcpy(path, commandPath);
    strcat(path, "/date");
    while (temp != NULL)
    {
        if (strcmp(temp, "-u") == 0)
        {
            flag_u = 1;
        }
        if (strcmp(temp, "-R") == 0)
        {
            flag_r = 1;
        }
        temp = strtok(NULL, " ");
        counter++;
    }
    if (counter < 2)
    {
        flag = 1;
    }
    if (flag_u == 1 && flag_r == 1)
    {
        printf("Enter correct commmand\n");
        return;
    }
    if (flag)
    {
        char *const argv[] = {path, NULL};
        pid = fork();
        if (pid == 0)
        {
            flag = 0;
            // printf("date command is called\n")s;
            execv(argv[0], argv);
            // perror("Return from execv() not expected");
            // printf("date command is finished\n");
            return;
        }
        else
        {
            wait(NULL);
        }
    }
    if (flag_u)
    {
        char *const argv[] = {path, "-u", NULL};
        pid = fork();
        if (pid == 0)
        {
            flag_u = 0;
            // printf("date command is called\n");
            execv(argv[0], argv);
            // perror("Return from execv() not expected");
            // printf("date command is finished\n");
            return;
        }
        else
        {
            wait(NULL);
        }
    }
    if (flag_r)
    {
        flag_r = 0;
        char *const argv[] = {path, "-R", NULL};
        pid = fork();
        if (pid == 0)
        {
            // printf("date command is called\n");
            execv(argv[0], argv);
            // perror("Return from execv() not expected");
            // printf("date command is finished\n");
            return;
        }
        else
        {
            wait(NULL);
        }
    }
}
void runLS(char *command)
{
    int index = 0;
    int flag = 0;
    int flag_a = 0;
    int flag_m = 0;
    int counter = 0;
    char path[100];
    strcpy(path, commandPath);
    strcat(path, "/ls");
    while (command != NULL)
    {
        if (strcmp(command, "-a") == 0)
        {
            flag_a = 1;
        }
        if (strcmp(command, "-m") == 0)
        {
            flag_m = 1;
        }
        command = strtok(NULL, " ");
        counter++;
    }
    if (counter < 2)
    {
        flag = 1;
    }
    if (flag_a == 1 && flag_m == 1)
    {
        printf("Enter correct commmand");
        return;
    }
    if (flag == 1)
    {

        // printf("%s", path);
        char *const argv[] = {path, NULL};
        pid = fork();
        if (pid == 0)
        {
            execv(argv[0], argv);
        }
        else
        {
            wait(NULL);
            return;
        }
    }
    if (flag_a)
    {
        //  printf("ls -a is called\n");

        char *const argv[] = {path, "-a", NULL};
        pid = fork();
        if (pid == 0)
        {
            execv(argv[0], argv);
        }
        else
        {
            wait(NULL);
            return;
        }
    }
    if (flag_m)
    {
        //  printf("ls -m is called\n");
        char *const argv[] = {path, "-m", NULL};
        pid = fork();
        if (pid == 0)
        {
            execv(argv[0], argv);
        }
        else
        {
            wait(NULL);
            return;
        }
    }
    printf("Enter right command\n");
    return;
}
void runCat(char *command)
{
    char *argv[10];
    int index = 0;
    char path[100];
    strcpy(path, commandPath);
    strcat(path, "/cat");
    for (int i = 0; i < 10; i++)
        argv[i] = (char *)malloc(100 * sizeof(char));
    strcpy(argv[index++], path);
    while (command != NULL)
    {
        if (strcmp(command, "cat") == 0)
        {
            command = strtok(NULL, " ");
            continue;
        }
        strcpy(argv[index++], command);
        command = strtok(NULL, " ");
    }
    argv[index++] = NULL;
    // for (int i=0; i<10; i++)
    //     printf("%s ",argv[i]);

    pid = fork();
    if (pid == 0)
    {
        // printf("cat called\n");
        execv(argv[0], argv);
        // printf("cat finished\n");
        return;
    }
    else
    {
        wait(NULL);
        return;
    }
}
void runRM(char *command)
{
    char *argv[10];
    int index = 0;
    char path[100];
    strcpy(path, commandPath);
    strcat(path, "/rm");
    for (int i = 0; i < 10; i++)
        argv[i] = (char *)malloc(100 * sizeof(char));
    strcpy(argv[index++], path);
    while (command != NULL)
    {
        if (strcmp(command, "rm") == 0)
        {
            command = strtok(NULL, " ");
            continue;
        }
        strcpy(argv[index++], command);
        command = strtok(NULL, " ");
    }
    argv[index++] = NULL;
    // for (int i=0; i<10; i++)
    //     printf("%s ",argv[i]);

    pid = fork();
    if (pid == 0)
    {
        // printf("cat called\n");
        execv(argv[0], argv);
        // printf("cat finished\n");
        return;
    }
    else
    {
        wait(NULL);
        return;
    }
}
void runMkdir(char *command)
{
    char *argv[10];
    int index = 0;
    char path[100];
    strcpy(path, commandPath);
    strcat(path, "/mkdir");
    for (int i = 0; i < 10; i++)
        argv[i] = (char *)malloc(100 * sizeof(char));
    strcpy(argv[index++], path);
    while (command != NULL)
    {
        if (strcmp(command, "mkdir") == 0)
        {
            command = strtok(NULL, " ");
            continue;
        }
        strcpy(argv[index++], command);
        command = strtok(NULL, " ");
    }
    argv[index++] = NULL;
    // for (int i=0; i<10; i++)
    //     printf("%s ",argv[i]);

    pid = fork();
    if (pid == 0)
    {
        // printf("cat called\n");
        execv(argv[0], argv);
        // printf("cat finished\n");
        return;
    }
    else
    {
        wait(NULL);
        return;
    }
}
void performExternal(char *command)
{
    if (strcmp(command, "date") == 0)
    {
        runDate(command);
        return;
    }
    if (strcmp(command, "ls") == 0)
    {
        runLS(command);
    }
    if (strcmp(command, "cat") == 0)
    {
        runCat(command);
    }
    if (strcmp(command, "rm") == 0)
    {
        runRM(command);
    }

    if (strcmp(command, "mkdir") == 0)
    {
        runMkdir(command);
    }
}

void performInternal(char *command)
{

    if (strcmp(command, "pwd") == 0)
    {
        char cwd[100];
        puts(getcwd(cwd, sizeof(cwd)));
        return;
    }
    if (strcmp(command, "history") == 0)
    {
        while (command != NULL)
        {
            if (strcmp(command, "-c") == 0)
            {
                printHistory("-c");
                return;
            }
            command = strtok(NULL, " ");
        }
        printHistory(" ");
        return;
    }
    if (strcmp(command, "echo") == 0)
    {
        char string[1000][1000];
        int index = 0;
        char flag[10];
        while (command != NULL)
        {
            if (index == 1 && strcmp(command, "-n") == 0)
            {
                strcpy(flag, "-n");
            }
             if (index == 1 && strcmp(command, "--help") == 0)
            {
                strcpy(flag, "--help");
            }
            strcpy(string[index++], command);
            command = strtok(NULL, " ");
        }
        if (strcmp(flag, "-n") == 0)
        {
            for (int i = 2; i < index; i++)
            {
                printf("%s ", string[i]);
            }
            return;
        }
         if (strcmp(flag, "--help") == 0)
        {
            printf("Echo the STRING(s) to standard output.\n-n do not output the trailing newline\n--help display this help and exit");
            return;
        }


        for (int i = 1; i < index; i++)
        {
            printf("%s ", string[i]);
        }
        printf("\n");
        return;
    }
    if (strcmp(command, "cd") == 0)
    {
        char path[10][100];
        int index = 0;
        while (command != NULL)
        {
            if (strcmp(command, "-L") == 0)
            {

                command = strtok(NULL, " ");
                continue;
            }
            strcpy(path[index++], command);
            command = strtok(NULL, " ");
        }
        int c = chdir(path[1]);
        if (c == -1)
        {
            printf(" No such file or directory\n");
        }
    }
}
int main() // start of the shell command prompt
{
    clear();
    int pid;
    char userCmdInput[100];
    getcwd(commandPath, sizeof(commandPath));
    username = getenv("USER");
    if (username == NULL)
        return EXIT_FAILURE;
    // printf("%s\n", username);
    strcat(history_path,username);
    strcat(history_path,"/.bash_history");

    // strcat(history_path, system("echo $USER"));
    // strcat(history_path,"/.bash_history");
    // printf("path %s", history_path);
    // printf("%s\n",username );

    while (1) // This is a infinite loop which won't terminate till it encounters a exit code zero;
    {
        char cwd[100];
        printf("%s@ubuntu:%s:~$ ",username,getcwd(cwd, sizeof(cwd))); //prompt for the command shell
        // scanf("%s",&userCmdInput);

        gets(userCmdInput);
        FILE *file;

        file = fopen(history_path, "a+");
        fputs(userCmdInput, file);
        fputs("\n", file);
        fclose(file);

        if (strlen(userCmdInput) == 0)
            continue;
        if (strcmp(userCmdInput, "cls") == 0)
        {
            clear();
            continue;
        }
        char *split = strtok(userCmdInput, " ");
        if (strcmp(userCmdInput, "exit") == 0)
        {

            return 0;
        }
        if (checkcommand(split) == -1)
        {
            puts("please enter right command\n");
            continue;
        }
        if (checkcommand(split) == 0)
        {
            // puts("Internal Command\n");
            performInternal(split);
            continue;
        }
        if (checkcommand(split) == 1)
        {
            // puts("External Command\n");
            performExternal(split);
            continue;
        } //gets the users input

        // system(userCmdInput); // parses the user input to the system and creates a new child process that executes the command given by the user and returns the value to the parent process which is the main code of out program
    }
    return 0;
}

// This is the other way implemetation of the Assignment question, here we directly call up a terminal and execute the require command, the cmdInput command tajes the input from the user and once the input is taken the string is compared in the condition and executed according to the condition ,other functionality of the command are explained in the code whereever required
