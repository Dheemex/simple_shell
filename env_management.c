#include "shell.h"

/**
 * env_get_key - it gets the value of an environment variable
 * @key: shows the environ variable of interest
 * @data: shows the struct of program's data
 * Return: a pointer to variable value or NULL if it doesn't exist
 */
char *env_get_key(char *key, data_of_program *data)
{
	int i, key_length = 0;

	/* it validate the arguments */
	if (key == NULL || data->env == NULL)
		return (NULL);

	/* it obtains the lenth of variable requested */
	key_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{/* List through the environ and check for coincidence of the name */
		if (str_compare(key, data->env[i], key_length) &&
		 data->env[i][key_length] == '=')
		{/* returns the value of the key NAME=  when find it*/
			return (data->env[i] + key_length + 1);
		}
	}
	/* returns NULL if did not found */
	return (NULL);
}

/**
 * env_set_key - it overwrite value of the environment variable
 * or create it if does not exist.
 * @key: shows the name of the variable to set
 * @value: shows the new value
 * @data: shows struct of the program's data
 * Return: 1 if the parameters are NULL, 2 if there is an error 0 if success.
 */

int env_set_key(char *key, char *value, data_of_program *data)
{
	int i, key_length = 0, is_new_key = 1;

	/* it validate the arguments */
	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	/* it obtains the length of the variable requested */
	key_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{/* goes through the environ and check for coincidence of the name */
		if (str_compare(key, data->env[i], key_length) &&
		 data->env[i][key_length] == '=')
		{/* If key already exists */
			is_new_key = 0;
			/* it frees the entire variable, it is new created below */
			free(data->env[i]);
			break;
		}
	}
	/* it makes a string of the form key=value */
	data->env[i] = str_concat(str_duplicate(key), "=");
	data->env[i] = str_concat(data->env[i], value);

	if (is_new_key)
	{/* if the variable is new, it is create at end of actual list and we need*/
	/* to put the NULL value in the next position */
		data->env[i + 1] = NULL;
	}
	return (0);
}

/**
 * env_remove_key - it remove a key from the environment
 * @key: this is the key to be removed
 * @data: shows the sructure of the program's data
 * Return: 1 if the key was removed, 0 if the key does not exist;
 */
int env_remove_key(char *key, data_of_program *data)
{
	int i, key_length = 0;

	/* it validate the arguments */
	if (key == NULL || data->env == NULL)
		return (0);

	/* it obtains the length of variable requested */
	key_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{/* check through the environ and checks for coincidences */
		if (str_compare(key, data->env[i], key_length) &&
		 data->env[i][key_length] == '=')
		{/* if key already exists, remove them */
			free(data->env[i]);

			/* it moves the others keys one position down */
			i++;
			for (; data->env[i]; i++)
			{
				data->env[i - 1] = data->env[i];
			}
			/* put the NULL value at the end of the list */
			data->env[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * print_environ - it prints the current environ
 * @data: shows struct for the program's data
 * Return: nothing
 */
void print_environ(data_of_program *data)
{
	int j;

	for (j = 0; data->env[j]; j++)
	{
		_print(data->env[j]);
		_print("\n");
	}
}
