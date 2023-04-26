#ifndef SHELL_H_
#define SHELL_H_

#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>

/* for command chaining */
#define CMD_NORM 0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN 3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked lists
 * @num: the num field
 * @str: a string
 * @next: it points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - it contains pseudo-arguements to pass into function,
 * allowing uniform prototype for function pointer struct
 * @fname: shows the program filename
 * @alias: shows the alias node
 * @argc: shows the argument count
 * @linecount_flag: if on count this line of input
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @argv: this is an array of strings generated from arg
 * @environ: shows custom modified copy of environ from LL env
 * @status: shows the return status of the last exec'd command
 * @histcount: shows the history line number count
 * @line_count: shows the error count
 * @history: shows the history node
 * @cmd_buf: shows address of pointer to cmd_buf, on if chaining
 * @path: shows a string path for the current command
 * @env_changed: shows on if environ was changed
 * @readfd: the fd from which to read line input
 * @arg: shows a string generated from getline containing arguements
 * @env: the linked list local copy of environ
 * @err_num: the error code for exit(s)
 */
typedef struct passinfo
{
	int argc;
	unsigned int line_count;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	int env_changed;
	int status;
	int err_num;
	int linecount_flag;
	char **argv;
	char *path;
	char *arg;
	char **environ;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int readfd;
	int histcount;
	int cmd_buf_type; /* CMD_type ||, &&, ; */
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - it contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the func
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* loophsh.c */
int loophsh(char **);

/* toem_atoi.c */
int _atoi(char *);
int interactive(info_t *);
int _isalpha(int);
int is_delim(char, char *);

/* toem_builtin.c */
int _mycd(info_t *);
int _myexit(info_t *);
int _myhelp(info_t *);

/* toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/* toem_environ.c */
int _myenv(info_t *);
char *_getenv(info_t *, const char *);
int _mysetenv(info_t *);
int populate_env_list(info_t *);
int _myunsetenv(info_t *);

/* toem_errors.c */
int _putfd(char c, int fd);
void _eputs(char *);
int _putsfd(char *str, int fd);
int _eputchar(char);

/* toem_errors1.c */
char *convert_number(long int, int, int);
int _erratoi(char *);
void remove_comments(char *);
int print_d(int, int);
void print_error(info_t *, char *);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strchr(char *, char);
char *_strncat(char *, char *, int);

/* toem_getenv.c */
char **get_environ(info_t *);
int _setenv(info_t *, char *, char *);
int _unsetenv(info_t *, char *);

/* toem_getinfo.c */
void clear_info(info_t *);
void free_info(info_t *, int);
void set_info(info_t *, char **);

/*toem_getline.c */
int _getline(info_t *, char **, size_t *);
ssize_t get_input(info_t *);
void sigintHandler(int);

/* toem_history.c */
char *get_history_file(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int read_history(info_t *info);
int renumber_history(info_t *info);
int write_history(info_t *info);

/* toem_lists.c */
int delete_node_at_index(list_t **, unsigned int);
list_t *add_node_end(list_t **, const char *, int);
list_t *add_node(list_t **, const char *, int);
size_t print_list_str(const list_t *);
void free_list(list_t **);

/* toem_lists1.c */
char **list_to_strings(list_t *);
list_t *node_starts_with(list_t *, char *, char);
size_t list_len(const list_t *);
size_t print_list(const list_t *);
ssize_t get_node_index(list_t *, list_t *);

/* toem_memory.c */
int bfree(void **);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *find_path(info_t *, char *, char *);
char *dup_chars(char *, int, int);

/* toem_realloc.c */
void *_realloc(void *, unsigned int, unsigned int);
char *_memset(char *, char, unsigned int);
void ffree(char **);

/* toem_shloop.c */
void find_cmd(info_t *);
int find_builtin(info_t *);
void fork_cmd(info_t *);
int hsh(info_t *, char **);

/* toem_string.c */
int _strlen(char *);
char *starts_with(const char *, const char *);
int _strcmp(char *, char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
void _puts(char *);
char *_strdup(const char *);
int _putchar(char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_vars.c */
int is_chain(info_t *, char *, size_t *);
int replace_alias(info_t *);
int replace_string(char **, char *);
int replace_vars(info_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);

#endif
