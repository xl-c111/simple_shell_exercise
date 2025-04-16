#include <stdio.h>
#include <unistd.h>
/**
 * main - fork example
 *
 * Return: Always 0.
 *
 * Description: getpid() returns the PID of current process
 *              Return value: - When called in the parent process, it returns the parent's PID
 *                            - When called in the child process, it returns the child's PID
 *
 *              fork() is used to create a new process
 *              Return values: - Negative value: Error occurred; child process not created
 *                             - 0: Returned in the child process
 *                             - Positive value: PID of the child process, returned in the parent process
 *
 *              Parent: getpid() = 1234, fork() return = 1235 (child PID)
 *              Child: getpid() = 1235, fork() return = 0
 *
 */
int main(void)
{
	pid_t my_pid;
	pid_t child_pid;
	
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (1);
	}
	
	my_pid = getpid();
	printf("My pid is %u\n", my_pid);
	
	if (child_pid == 0)
	{
		printf("(%u) Nooooooooo!\n", my_pid);
	}
	else
	{
		printf("(%u) %u, I am your father\n", my_pid, child_pid);
	}
	return (0);
}
