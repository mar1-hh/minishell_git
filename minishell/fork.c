#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
       #include <sys/wait.h>

int main()
{
    char *matr[] = {"ls", NULL};
    char *matr2[] = {"cat", NULL};
    int pid1;
    int pide2;
    int    arr[2];

    pipe(arr);
    pid1 = fork();
    if (!pid1)
    {
        close(arr[0]);
        dup2(arr[1], 1);
        close(arr[1]);
        execve("/usr/bin/ls", matr, NULL);
        exit(1);
    }
    pide2 = fork();
    if (!pide2)
    {
        close(arr[1]);
        dup2(arr[0], 0);
        close(arr[0]);
        execve("/usr/bin/cat", matr2, NULL);
        exit(1);
    }
    close(arr[0]);
    close(arr[1]);
    wait(NULL);
    wait(NULL);
    return (0);
}