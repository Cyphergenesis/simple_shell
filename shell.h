#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

#define CONVERT_LOWERCASE  1
#define CONVERT_UNSIGNED   2

#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE "simple_shel_history"
#define HIST_MAX  4096

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
} lis_t;
/**
* struct passinfo - contains pseudo-arguements to pass into a function,
* allowing uniform prototype for function pointer struct
* @ag: a string generated from getline containing arguements
* @agv:an array of strings generated from arg
* @pth: a string path for the current command
* @agc: the argument count
* @line_count: the error count
* @err_num: the error code for exit()s
* @line_flag: if on count this line of input
* @_name: the program filename
* @env: linked list local copy of environ
* @environ: custom modified copy of environ from LL env
* @history: the history node
* @alias: the alias node
* @_changed_env: on if environ was changed
* @-stat: the return status of the last exec'd command
* @cmd_buff: address of pointer to cmd_buf, on if chaining
* @cmd_type: CMD_type ||, &&, ;
* @fdRead: the fd from which to read line input
* @_count_num: the history line number count
*/

typedef struct passinfo
{
char *arg;
char **argv;
char *path;
int argc;
unsigned int line_count;
int _num;
int line_flag;
char *_name;
lis_t *env;
lis_t *history;
lis_t *alias;
char **environ;
int _changed_env;
int _stat;
char **cmd_buff; /* pointer to cmd ; chain buffer, for memory mangement */
int cmd_type; /* CMD_type ||, &&, ; */
int _fdRead;
int _count_num;
}sort;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}
/**
* struct builtin - contains a builtin string and related function
* @type: the builtin command flag
* @func: the function
*/
typedef struct builtin
{
char *type;
int (*func)(sort *);
} buil_tab;

/* _active-shell.c*/
int _active(sort *f);
int checks_delim(char s, char *del);
int checks_alpha(int c);
int _convert_str(char *m);

/*_built.c*/
int _chdirectory(sort *f);
int _chcd(sort *f);
int _ex_shell(sort *f);

/* builtin1.c */
int _alias(sort *f);
int alias_string(lis_t *node);
int make_alias(sort *f, char *str);
int unmake_alias(sort *f, char *str);
int _display_list(sort *f);

/* _1-environ.c */
int curr_env(sort *f);
char *_get_env(sort *f, const char *u_name);
int new_env(sort *f);
int _rem_environ(sort *f);
int stuff_list(sort *f);

/* _errors.c */
int _print_string(char *ptr, int fd);
int write_fd(char k, int fd);
int _write(char s);
void _write_str(char *str);


/* _error-1.c */
int con_str(char *str);
void _error(sort *f, char *str);
int print_func(int inp, int fd);
char *con_num(long int num, int b, int flags);
void rep_lines(char *bf);

/* _ex-strins.c */
char *str_cp(char *des, char *src, int num);
char *_str_cat(char *des, char *src, int num);
char *locate_str(char *str, char c);

/* catchline.c */
ssize_t cha_buff(sort *f, char **buff, size_t *length);
ssize_t _input(sort *f);
ssize_t read_buffer(sort *f, char *buff, size_t *n);
int _get_line(sort *f, char **ptr, size_t *len);
void signint(__attribute__((unused))int sig_num);

/* surf-environment */
char **_environ(sort *f);
int _unsetenv(sort *f, char *v);
int _setenv(sort *f, char *v, char *val);


/* _info-shell */
void _clear(sort *f);
void _info(sort *f, char **av);
void release_sort(sort *f, int a);

/* _past-check */
int renum_link(sort *f);
int add_list(sort *f, char *buff, int line_count);
int _read(sort *f);
int _create(sort *f);
char *gets_file(sort *f);

/* _ls  */
lis_t *_node(lis_t **head, const char *st, int n);
lis_t *_addnode(lis_t **head, const char *st, int nm);
size_t write_str(const lis_t *head);
int del_node(lis_t **head, unsigned int ind);
void distro_list(lis_t **h_ptr);


/* _ls-1 */
size_t _lenlist(const lis_t *head);
char **list_strings(lis_t *head);
size_t list_link(const lis_t *head);
lis_t *_node_prefix(lis_t *node, char *pref, char c);
ssize_t get_index(lis_t *head, lis_t *node);

/* main  */
int main(int ac, char **av);

/* size */
int _free(void **p);

/* count */
int _cmd(sort *f, char *path);
char *_chars_dup(char *pstr, int start, int stop);
char *_path_cmd(sort *f, char *pstr, char *cmd);

/* reall */

char *_mem(char *p, char byte, unsigned int num);
void _free_str(char **qq);
void *_reall(void *ptr, unsigned int old, unsigned int new_s);

/* shell */
int _hsh(sort *f, char **av);
int _builtin(sort *f);
void _find(sort *f);
void _fork(sort *f);

/* _str */
int _strl(char *r);
int _strcm(char *str1, char *str2);
char *start_hay(const char *str, const char *sub);
char *_strc(char *des, char *sr);

/* _str-1 */
char *strcp(char *des, char *sr);
char *_dup(const char *str);
void putst(char *st);
int putch(char c);

/* Token */
char **tow(char *st, char *delim);
char **tow1(char *str, char delim);

/* variable */
int _chain(sort *f, char *buff, size_t *cur);
void ch_chain(sort *f, char *buff, size_t *q, size_t i, size_t len);
int rep_alia(sort *f);
int rep_var(sort *f);
int rep_str(char **oldstr, char *newstr);

/*-------------------------------------------------------------*/

#endif
