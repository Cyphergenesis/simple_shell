#include "shell.h"
/**
* _node - adds a node to the start of the list
* @head: address of pointer to head node
* @st: str field of node
* @n: node index used by history
*
* Return: size of list
*/
lis_t *_node(lis_t **head, const char *st, int n)
{
	lis_t *new;

	if (!head)
		return (NULL);

	new = malloc(sizeof(lis_t));
	if (!new)
		return (NULL);
	_mem((void *)new, 0, sizeof(lis_t));
	new->num = n;
	if (st)
	{
		new->str = _dup(st);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}

	new->next = *head;
	*head = new;

	return (new);

}
/**
* _addnode - adds a node to the end of the list
* @head: address of pointer to head node
* @st: str field of node
* @nm: node index used by history
*
* Return: size of list
*/
lis_t *_addnode(lis_t **head, const char *st, int nm)
{
	lis_t *new, *node;

	if (!head)
		return (NULL);

	node = *head;
	new = malloc(sizeof(lis_t));
	if (!new)
		return (NULL);
	_mem((void *)new, 0, sizeof(lis_t));
	new->num = nm;
	if (st)
	{
		new->str = _dup(st);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}

	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new;
	}
	else
		*head = new;
	return (new);

}
/**
* write_str - prints only the str element of a list_t linked list
* @h: pointer to first node
*
* Return: size of list
*/
size_t write_str(const lis_t *head)
{
	size_t i = 0;

	while (head)
	{
		putst(head->str ? head->str : "(nil)");
		putst("\n");
		head = head->next;
		i++;
	}
	return (i);

}
/**
* del_node - deletes node at given index
* @head: address of pointer to first node
* @ind: index of node to delete
*
* Return: 1 on success, 0 on failure
*/
int del_node(lis_t **head, unsigned int ind)
{
	lis_t *node, *p_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!ind)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == ind)
		{
			p_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		p_node = node;
		node = node->next;
	}

	return (0);
}
/**
* distro_list - frees all nodes of a list
* @h_ptr: address of pointer to head node
*
* Return: void
*/
void distro_list(lis_t **h_ptr)
{
	lis_t *node, *next_node, *head;

	if (!h_ptr || !*h_ptr)
		return;

	head = *h_ptr;
	node = head;

	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*h_ptr = NULL;

}
