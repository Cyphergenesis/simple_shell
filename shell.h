#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
/* for command chaining */
#define CMD_NORM 0
#define CMD_OR  1
#define CMD_AND  2
#define CMD_CHAIN 3

/* for convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED   2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE  ".simple_shell_history"
#define HIST_MAX   4096


extern char **environ;
/**
* struct liststr - singly linked list
* @num: the number field
* @str: a string
* @next: points to the next node
*/
typedef struct liststr
{
int num;
char *str;
struct liststr *next;
} list_t;
/*** struct passinfo - contains pseudo-arguements to pass into a function,
* allowing uniform prototype for function pointer struct
* @arg: a string generated from getline containing arguements
* @argv:an array of strings generated from arg
* @path: a string path for the current command
* @argc: the argument count
* @line_count: the error count
* @err_num: the error code for exit()s
* @linecount_flag: if on count this line of input
* @fname: the program filename
* @env: linked list local copy of environ
* @environ: custom modified copy of environ from LL env
* @history: the history node
* @alias: the alias node
* @env_changed: on if environ was changed
* @status: the return status of the last exec'd command
* @cmd_buf: address of pointer to cmd_buf, on if chaining
* @cmd_buf_type: CMD_type ||, &&, ;
* @readfd: the fd from which to read line input
* @histcount: the history line number count
*/
typedef struct passinfo
{
char *arg;
char **argv;
char *path;
int argc;
unsigned int line_count;
int err_num;
int linecount_flag;
char *fname;
list_t *env;
list_t *history;
list_t *alias;
char **environ;
int env_changed;
int status;
char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
int cmd_buf_type; /* CMD_type ||, &&, ; */
int readfd;
int histcount;
} sort;
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}/**
* struct builtin - contains a builtin string and related function
* @type: the builtin command flag
* @func: the function
*/
typedef struct builtin
{
char *type;
int (*func)(sort *);
} builtin_table;

/* vars */

int _chain(sort *f, char *buf, size_t *p);
void ch_chain(sort *f, char *buf, size_t *p, size_t i, size_t len);
int rep_alia(sort *f);
int rep_var(sort *f);
int rep_str(char **old, char *new);

/* atoi */
int _active(sort *f);
int checks_delim(char s, char *del);
int checks_alpha(int c);
int _convert_str(char *m);

/* builtin */
int _chdirectory(sort *f);
int _chcd(sort *f);
int _ex_shell(sort *f);

/* builtin1 */
int _alias(sort *f);
int alias_string(list_t *node);
int make_alias(sort *f, char *str);
int unmake_alias(sort *f, char *str);
int _display_list(sort *f);

/* environ */

int stuff_list(sort *f);
int _rem_environ(sort *f);
int new_env(sort *f);
char *_get_env(sort *f, const char *name);
int curr_env(sort *f);

/* error1 */

void rep_lines(char *buf);
char *con_num(long int num, int base, int flags);
int print_func(int input, int fd);
void _error(sort *f, char *estr);
int con_str(char *s);

/* errors */
int _print_string(char *str, int fd);
int write_fd(char c, int fd);
int _write(char c);
void _write_str(char *str);

/* exits */
char *_str_cat(char *dest, char *src, int n);
char *locate_str(char *s, char c);
char *str_cp(char *dest, char *src, int n);

/* getinfo */
void _clear(sort *f);
void _info(sort *f, char **av);
void release_sort(sort *f, int a);

/* getline */
void signint(__attribute__((unused))int sig_num);
int _get_line(sort *f, char **ptr, size_t *length);
ssize_t read_buffer(sort *f, char *buf, size_t *i);
ssize_t _input(sort *f);
ssize_t cha_buff(sort *f, char **buff, size_t *len);

/* history */
int renum_link(sort *f);
int add_list(sort *f, char *buf, int linecount);
int _read(sort *f);
int _create(sort *f);
char *gets_file(sort *f);

/* lists */
void distro_list(list_t **head_ptr);
int del_node(list_t **head, unsigned int index);
size_t print_list_str(const list_t *h);
list_t *_addnode(list_t **head, const char *str, int num);
list_t *_node(list_t **head, const char *str, int num);
size_t write_str(const list_t *h);

/* list1 */
ssize_t get_index(list_t *head, list_t *node);
list_t *_node_prefix(list_t *node, char *prefix, char c);
size_t list_link(const list_t *h);
char **list_strings(list_t *head);
size_t _lenlist(const list_t *h);

/* main */
int main(int ac, char **av);

/*memory */
int _free(void **ptr);

/* parser */
int _cmd(sort *f, char *path);
char *_chars_dup(char *pathstr, int start, int stop);
char *_path_cmd(sort *f, char *pathstr, char *cmd);

/* realloc */
void *_reall(void *ptr, unsigned int old_size, unsigned int new_size);
void _free_str(char **pp);
char *_mem(char *s, char b, unsigned int n);

/* shell_loop */
void _fork(sort *f);
void _find(sort *f);
int _builtin(sort *f);
int _hsh(sort *f, char **av);

/* string */
char *_strc(char *dest, char *src);
char *start_hay(const char *haystack, const char *needle);
int _strcm(char *s1, char *s2);
int _strl(char *s);

/* string1 */
int putch(char c);
void putst(char *str);
char *_dup(const char *str);
char *strcp(char *dest, char *src);

/* token */

char **tow(char *str, char *d);
char **tow1(char *str, char d);

/* getenv */
char **_environ(sort *f);
int _unsetenv(sort *f, char *var);
int _setenv(sort *f, char *var, char *value);


#endif
