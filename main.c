#include "shell.h"

/**
<<<<<<< HEAD
 *  main - This is the  entry point
 *  @ac: shows the arg count
 *  @av: shows the arg vector
 *
 *  Return: 0 on success, 1 on error
 */
int main(int ac, char **av)

{
	info_t info[] = { INFO_INIT };
	int fd = 2
		
		asm ("mov %1, %0\n\t"
				"add $3, %0"
				: "=r" (fd)
				: "r" (fd));
	if (ac == 2)
=======
 * main - func that initialize the variables of the program
 * @argc: number of values received from the command line
 * @argv: values received from the command line
 * @env: number of values received from the command line
 * Return: 0 on succes.
 */

int main(int argc, char *argv[], char *env[])
{
	data_of_program data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	inicialize_data(data, argc, argv, env);

	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	sisifo(prompt, data);
	return (0);
}

/**
 * handle_ctrl_c - print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is send to the program
 * @UNUSED: option of the prototype
 */
void handle_ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * inicialize_data - func that inicialize the struct with the info of the program
 * @data: pointer to the structure of data
 * @argv: array of arguments pased to the program execution
 * @env: environ pased to the program execution
 * @argc: number of values received from the command line
 */
void inicialize_data(data_of_program *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;

	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_printe(data->program_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
>>>>>>> 0e5082bba5e66bcac844cfff8c5a97f6861804f6
	{
		for (; env[i]; i++)
		{
			data->env[i] = str_duplicate(env[i]);
		}
	}
	data->env[i] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->alias_list[i] = NULL;
	}
}
/**
 * sisifo - an infinite loop function that shows the prompt
 * @prompt: this is the prompt to be printed
 * @data: loop that shows the prompt
 */
void sisifo(char *prompt, data_of_program *data)
{
	int error_code = 0, string_len = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
		error_code = string_len = _getline(data);

		if (error_code == EOF)
		{
			free_all_data(data);
			exit(errno);
		}
		if (string_len >= 1)
		{
			expand_alias(data);
			expand_variables(data);
			tokenize(data);
			if (data->tokens[0])
			{
<<<<<<< HEAD
				_eputs(av[0];
				_eputs(": 0: Can't open ");
				_eputs(av[1];
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
=======
				error_code = execute(data);
				if (error_code != 0)
					_print_error(error_code, data);
>>>>>>> 0e5082bba5e66bcac844cfff8c5a97f6861804f6
			}
			free_recurrent_data(data);
		}
	}
<<<<<<< HEAD
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);;
=======
>>>>>>> 0e5082bba5e66bcac844cfff8c5a97f6861804f6
}
