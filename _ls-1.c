#include "shell.h"
/**
* _lenlist - determines length of linked list
* @head: pointer to first node
*
* Return: size of list
*/
size_t _lenlist(const lis_t *head)
{
	size_t i = 0;

	while (head)
	{
		head = head->next;
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
char **list_strings(lis_t *head)
{
	lis_t *node = head;

	size_t i = _lenlist(head);
	size_t k;
	char  **strings;
	char *str;

	if (!head || !i)
		return (NULL);

	strings = malloc(sizeof(char*)* (1 + 1));

	if (!strings)
		return (NULL);

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strl(node->str) + 1);
		if(!str)
		{
			for (k = 0; k < i; k++)
				free(strings[k]);
			free(strings);
			return(NULL);
		}
		str = strcp(str, node->str);
		strings[i] = str;

	}

	strings[i] = NULL;
	return (strings);

}

/**
* list_link - prints all elements of a list_t linked list
* @head: pointer to first node
*
* Return: size of list
*/
size_t list_link(const lis_t *head)
{
	size_t j = 0;
	
	while (head)
	{
		putst(con_num(head->num, 10, 0));
		putch(':');
		putch(' ');
		putst(head->str ? head->str : "(nil)");
		putst("\n");
		head = head->next;
		j++;
	}
	
	return (j);
}

/**
* _node_prefix - returns node whose string starts with prefix
* @node: pointer to list head
* @pref: string to match* 
* @c: the next character after prefix to match
*
* Return: match node or null
*/

lis_t *_node_prefix(lis_t *node, char *pref, char c)
{
	char *h = NULL;
	
	while (node)
	{
		 h = start_hay(node->str, pref);
		if (h && ((c == -1) || (*h == c)))
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
ssize_t get_index(lis_t *head, lis_t *node)
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
