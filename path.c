#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * main - a simplified version of the 'which' command
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on error
 *
 * Description: 
 * 1, get the list of command names from the user
 *              
 * 2, retrieve and parse the PATH environment variable
 *              char *getenv(const char *name);
 *              getenv() is a function used to get the value of an environment variable
 *              @name: the name of variable you want to retrieve
 *
 *              char *strdup(const char *s);     ---->>> copy + allocate new memory
 *              - strdup duplicates a string by allocating new memory and copying the original content into it
 *              - @s: the string to be copied
 *              - Return: a pointer to the newly duplicated string, NULL if fails
 *
 * 3, For each directory in PATH, build the full command path
 *              int snprintf(char *str, size_t size, const char *format, ...);
 *              - @str: the destination buffer 
 *              - @size: maximum number of bytes to write (including \0)
 *              - @format: format string (like printf)
 *              - ...values to fill into the format
 *
 * 4, Use access() to check if the file exists and is executable
 *              int access(const char *pathname, int mode);
 *              - check if the file pointed to by fullpath exists and is executable
 *              - @pathname: path of the file to check
 *              - mode: permission to check (read, write, execute, etc.)
 *                      - X_OK: check if executable
 *                      - R_OK: check if readable
 *                      - W_OK: check if writable
 *                      - F_OK: check if file exists
 *
 *
 */

int main(int argc, char *argv[])
{
	char *path_env, *path_copy, *token;
	char fullpath[1024];
	int i;
	
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s filename ...\n", argv[0]);
		return 1;
	}

	path_env = getenv("PATH");       /* path_env is char* variable pointes the string returned by getenv() */
	if (!path_env)                   /* if path not found */
	{
		perror("getenv PATH");
		return 1;
	}
	
	for (i = 1; i < argc; i++)       /* loop through each command-line argument, skip argv[0] */
	{
		int found = 0;
		path_copy = strdup(path_env);  /* allocate memory and copy the contents of string path_env into new allocation */
		
		if (!path_copy)                /* if allocation fails */
		{
			perror("strdup");
			return 1;
		}
		
		token = strtok(path_copy, ":");      /* split the PATH string by : to get individual directories */
		
		while (token != NULL)               
		{
			/* build the full path to the file by  combining the directory name (token) */                                                                                            /* and the filename (argv[i]) and writes it into the buffer fullpath */
			snprintf(fullpath, sizeof(fullpath), "%s/%s", token, argv[i]);
			
			if (access(fullpath, X_OK) == 0)        /* check if the file exists and is executable */
			{
				printf("%s\n", fullpath);
				found = 1;
				break;
			}
			token = strtok(NULL, ":");     /* move to the next directory in PATH */
		}
		
		if (!found)
			printf("%s: not found\n", argv[i]);
		free(path_copy);
	}
	return 0;
}

