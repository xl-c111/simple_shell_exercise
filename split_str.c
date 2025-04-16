#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * split_string - splits a string
 * @str: a pointer to string
 *
 * Return: an array of each word of the string
 */
char **split_string(char *str)
{
	int i = 0;
	int bufsize = 64;
	char **tokens = malloc(sizeof(char *) * bufsize);
	char *token;

	if (tokens == NULL)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	
	token = strtok(str, " \t\r\n");
	while (token != NULL)
	{
		tokens[i++] = token;

		if (i >= bufsize)
		{
			bufsize += 64;
		}
		tokens = realloc(tokens, sizeof(char *) * bufsize);
		if (tokens == NULL)
		{
			perror("realloc failed");
			exit(EXIT_FAILURE);
		}
		token = strtok(NULL, " \t\r\n");
	}
	tokens[i] = NULL;
	return (tokens);
}
int main()
{
	char input[] = "hello world this is Holberton School";
	char **words = split_string(input);
	
	for (int i = 0; words[i] != NULL; i++) 
	{
		printf("word[%d]: %s\n", i, words[i]);
	}
	free(words);
	return 0;
}
