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
char *ag;
char **agv;
char *pth;
int agc;
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


size_t _lenlist(const lis_t *head);
ssize_t get_index(lis_t *head, lis_t *node);
lis_t *_node_prefix(lis_t *node, char *pref, char c);
char **list_strings(lis_t *head);
void _info(sort *f, char **av);
void _clear(sort *f);


size_t list_link(const lis_t *head);
char *start_hay(const char *str, const char *sub);
int putch(char c);
char *_chars_dup(char *pstr, int start, int stop);

int curr_env(sort *f);
char *_get_env(sort *f, const char *u_name);
int new_env(sort *f);
int _rem_environ(sort *f);
int stuff_list(sort *f);

/* Errors */
void _write_str(char *str);
int _write(char s);
int write_fd(char k, int fd);
int _print_string(char *ptr, int fd);


int con_str(char *str);
void _error(sort *f, char *str);
int print_func(int inp, int fd);
char *con_num(long int num, int b, int flags);
void rep_lines(char *bf);

/*------------------------------------------------*/

/* strings*/
lis_t *_node(lis_t **head, const char *st, int n);
lis_t *_addnode(lis_t **head, const char *st, int nm);
size_t write_str(const lis_t *head);
int del_node(lis_t **head, unsigned int ind);
void distro_list(lis_t **h_ptr);
/*------------------------------------------*/

int _hsh(sort *f, char **av);
int _builtin(sort *f);
void _find(sort *f);
void _fork(sort *f);

char **_environ(sort *f);
int _remove_env(sort *f, char *v);
int init_env(sort *f, char *v, char *val);



int _active(sort *f);
int checks_delim(char s, char *del);
int checks_alpha(int c);
int _convert_tr(char *m);


int main(int ac, char **av);

char **tow(char *st, char *delim);
char **tow1(char *str, char delim);


int _ex_shell(sort *f);
int _chcd(sort *f);
int _chdirectory(sort *f);

char *str_cp(char *des, char *src, int num);
char *_str_cat(char *des, char *src, int num);
char *locate_str(char *str, char c);


char *gets_file(sort *f);
int _create(sort *f);
int _read(sort *f);
int add_list(sort *f, char *buff, int line_count);
int renum_link(sort *f);

int _free(void **p);
int _chain(sort *f, char *buff, size_t *cur);
void ch_chain(sort *f, char *buff, size_t *q, size_t i, size_t len);
int rep_alia(sort *f);
int rep_var(sort *f);
int rep_str(char **oldstr, char *newstr);

ssize_t cha_buff(sort *f, char **buff, size_t *length);
ssize_t _input(sort *f);
ssize_t read_buffer(sort *f, char *buff, size_t *n);
int _get_line(sort *f, char **ptr, size_t *len);
void signint(__attribute__((unused))int sig_num);

void release_sort(sort *f, int a);

void *_reall(void *ptr, unsigned int old, unsigned int new_s);
void _free_str(char **qq);
char *_mem(char *p, char byte, unsigned int num);

int _strl(char *r);
int _strcm(char *str1, char *str2);
char *start_hay(const char *str, const char *sub);
char *_strc(char *des, char *sr);

int _free(void **p);

char *strcp(char *des, char *sr);
char *_dup(const char *str);
void putst(char *st);

char *strcp(char *des, char *sr);
char *_dup(const char *str);
void putst(char *st);
int putch(char c);

int _display_list(sort *f);
int unmake_alias(sort *f, char *str);
int make_alias(sort *f, char *str);
int alias_string(lis_t *node);
int _alias(sort *f);

int _cmd(sort *f, char *path);
char *_chars_dup(char *pstr, int start, int stop);
char *_path_cmd(sort *f, char *pstr, char *cmd);



#endif
