#include "shell.h"

/**
 * main - sis
 *
 */

int main(void)
{
    int i = 0;

    for (; i < 5; i++)
    {
        if (fork() == 0)
        {
            execl("/bin/ls", "ls", "-l", "/tmp", NULL);
            return (0);
        }
        wait(NULL);
    }
    return (0);
}