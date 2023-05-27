#include "shell.h"
/**
* _lenlist - determines length of linked list
* @h: pointer to first node
*
* Return: size of list
*/
size_t _lenlist(const list_t *h)
{
	size_t i = 0;
	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}
/**
* list_strings - returns an array of strings of the list->str
* @head: pointer to first node
*
* Return: array of strings
*/
char **list_strings(list_t *head)
{
	list_t *node = head;
	size_t i = _lenlist(head), j;
	char **strs;
	char *str;
	if (!head || !i)
	return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));if (!strs)
	return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strl(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
			free(strs[j]);
			free(strs);
			return (NULL);
		}
			str = strcp(str, node->str);
			strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}
/**
* list_link - prints all elements of a list_t linked list
* @h: pointer to first node
*
* Return: size of list
*/
size_t list_link(const list_t *h)
{
	size_t i = 0;
	while (h)
	{
		putst(con_num(h->num, 10, 0));
		putch(':');
		putch(' ');
		putst(h->str ? h->str : "(nil)");
		putst("\n");
		h = h->next;
		i++;
	}
	return (i);
}
/**
* _node_prefix- returns node whose string starts with prefix
* @node: pointer to list head
* @prefix: string to match* @c: the next character after prefix to match
*
* Return: match node or null
*/
list_t *_node_prefix(list_t *node, char *prefix, char c)
{
	char *p = NULL;
	while (node)
	{
		p = start_hay(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
		return (node);
		node = node->next;
	}
	return (NULL);
}
/**
* get_index - gets the index of a node
* @head: pointer to list head
* @node: pointer to the node
*
* Return: index of node or -1
*/
ssize_t get_index(list_t *head, list_t *node)
{
	size_t i = 0;
	while (head)
	{
		if (head == node)
		return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
