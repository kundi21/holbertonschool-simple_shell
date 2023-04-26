#include "shell.h"

/**
 * main - function to get the process id's
 *
 * Pid & Ppid
 * get pid get the parent of the pid
 *
 * Return: always 0, success
 */

int main(void)
{
	int p_id, p_pid;

	p_id = getpid(); /*process id*/
	p_pid = getppid(); /*parent process id*/

	printf("Process ID: %d\n", p_id);
	printf("Parent Process ID: %d\n", p_pid);

	return (0);
}
