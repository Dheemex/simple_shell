#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

/********* MACROS ********/

#include "macros.h"

/************* STRUCTURES **************/

/**
 * struct info- shows the struct for program's data
 * @program_name: this is the name of the executable
 * @input_line: this is the pointer to input read for _getline
 * @command_name: this is pointer to first command typed by the user
 * @exec_counter: the num of excecuted commands
 * @file_descriptor: the file descriptor to input of commands
 * @tokens: shows pointer to array of tokenized input
 * @env: shows the copy of the environ
 * @alias_list: shows all array of pointers with aliases.
 */
typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} data_of_program;

/**
 * struct builtins - this shows the struct for builtins
 * @builtin: this is the name of the builtin
 * @function: this is the function to be called for every builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(data_of_program *data);
} builtins;


/****** MAIN FUNCTIONS ******/


/*========  shell.c  ========*/

/* It inicialize struct with nfo of program */
void inicialize_data(data_of_program *data, int arc, char *argv[], char **env);

/* it makes the infinite loop that do shows the prompt*/
void sisifo(char *prompt, data_of_program *data);

/* It print prompt in a new line */
void handle_ctrl_c(int opr UNUSED);


/*========  _getline.c  ========*/

/* it reads one line of standard input*/
int _getline(data_of_program *data);

/* it split each line for logical operators if it do exist */
int check_logic_ops(char *array_commands[], int i, char array_operators[]);


/*======== expansions.c ========*/

/* expand variables */
void expand_variables(data_of_program *data);

/* expand aliases */
void expand_alias(data_of_program *data);

/* it appends the string to end of buffer*/
int buffer_add(char *buffer, char *str_to_add);


/*======== str_tok.c ========*/

/* it separate the string in tokens with the use of delimiter */
void tokenize(data_of_program *data);

/* it creates a pointer to part of string */
char *_strtok(char *line, char *delim);


/*======== execute.c ========*/

/* It execute command with its entire path */
int execute(data_of_program *data);


/*======== builtins_list.c ========*/

/* If match a builtin, it executes it */
int builtins_list(data_of_program *data);


/*======== find_in_path.c ========*/

/* It creates an array of path directories */
char **tokenize_path(data_of_program *data);

/* It search for program in path */
int find_program(data_of_program *data);


/******* HELPERS FOR MEMORY MANAGEMENT *******/


/*======== helpers_free.c ========*/

/* it Frees the memory for directories */
void free_array_of_pointers(char **directories);

/* it Frees the fields needed each loop */
void free_recurrent_data(data_of_program *data);

/* it Frees all field of the data */
void free_all_data(data_of_program *data);


/************** BUILTINS **************/


/*======== builtins_more.c ========*/

/* it Closes the shell */
int builtin_exit(data_of_program *data);

/* it Changes the current directory */
int builtin_cd(data_of_program *data);

/* it set the work directory */
int set_work_directory(data_of_program *data, char *new_dir);

/* it shows help information */
int builtin_help(data_of_program *data);

/* it set, unset and show alias */
int builtin_alias(data_of_program *data);


/*======== builtins_env.c ========*/

/* It shows the environ where the shell runs */
int builtin_env(data_of_program *data);

/* It create or override a variable of environ */
int builtin_set_env(data_of_program *data);

/* it delete a variable of environ */
int builtin_unset_env(data_of_program *data);


/******* HELPERS FOR ENVIRON VARIABLES MANAGE **********/


/*======== env_management.c ========*/

/* it gets the value of an environ variable */
char *env_get_key(char *name, data_of_program *data);

/* It overwrites the value of the environ variable */
int env_set_key(char *key, char *value, data_of_program *data);

/* It remove a key from the environ */
int env_remove_key(char *key, data_of_program *data);

/* it prints the current environ */
void print_environ(data_of_program *data);


/************** HELPERS FOR PRINTING **************/


/*======== helpers_print.c ========*/

/* it prints string in the standard output */
int _print(char *string);

/* Its prints a string in the standard error */
int _printe(char *string);

/* It's prints a string in the standard error */
int _print_error(int errorcode, data_of_program *data);


/******* HELPERS FOR STRINGS MANAGEMENT *******/


/*======== helpers_string.c ========*/

/* It counts the num of charac of a string */
int str_length(char *string);

/* It duplicates a string */
char *str_duplicate(char *string);

/* It compares two strings */
int str_compare(char *string1, char *string2, int number);

/* It concatenates two strings */
char *str_concat(char *string1, char *string2);

/* It reverse a string */
void str_reverse(char *string);


/*======== helpers_numbers.c ========*/

/* It cast from int to string */
void long_to_string(long number, char *string, int base);

/* it convert a string to num */
int _atoi(char *s);

/* it count the coincidences of chact in string */
int count_characters(char *string, char *character);


/*======== alias_management.c ========*/

/* it print the list of alias */
int print_alias(data_of_program *data, char *alias);

/* it get the alias name */
char *get_alias(data_of_program *data, char *alias);

/* it set the alias name */
int set_alias(char *alias_string, data_of_program *data);


#endif
