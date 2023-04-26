#include "shell.h"
/**
 * execute - it executs command with entire path variables.
 * @data: shows a pointer to the program's data
 * Return: If success returns zero, otherwise, return -1.
 */
int execute(data_of_program *data)
{
	int retval = 0, status;
	pid_t pidd;

	/* check for program being inbuilt ins */
	retval = builtins_list(data);
	if (retval != -1)/* if program was found inbuilt ins */
		return (retval);

	/* to check for program file system */
	retval = find_program(data);
	if (retval)
	{/* if program is not found */
		return (retval);
	}
	else
	{/* if program was found */
		pidd = fork(); /* create a child process */
		if (pidd == -1)
		{ /* if the fork call failed */
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{/* I am the child process, I execute the program*/
			retval = execve(data->tokens[0], data->tokens, data->env);
			if (retval == -1) /* if error when execute*/
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{/* I am the father, I check the exit status of the child */
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
