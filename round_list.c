/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 14:47:48 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/01 19:29:24 by gcerrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_codex.h"

// Alloca la memoria per un nuovo nodo e lo inizializza
t_node	*create_node(t_coder new_coder)
{
	t_node	*coder_place;

	coder_place = malloc(sizeof(t_node));
	if (!coder_place)
		return (NULL);
	coder_place->data = new_coder;
	coder_place->next = NULL;
	coder_place->prev = NULL;
	return (coder_place);
}

// Inserisce un nodo all'inizio (subito dopo la tail)
void	insert_head(t_node **tail, t_coder new_coder)
{
	t_node	*new_node;

	new_node = create_node(new_coder);
	if (*tail == NULL)
	{
		new_node->next = new_node;
		*tail = new_node;
	}
	else
	{
		new_node->next = (*tail)->next;
		new_node->next->prev = *tail;
		(*tail)->next = new_node;
	}
}

// Inserisce un nodo alla fine (diventa la nuova tail)
void	insert_tail(t_node **tail, t_coder new_coder)
{
	t_node	*new_node;
	t_node	*temp;

	new_node = create_node(new_coder);
	if (*tail == NULL)
	{
		new_node->next = new_node;
		tail = &new_node;
	}
	else
	{
		new_node->next = (*tail)->next;
		(*tail)->next = new_node;
		temp = (*tail);
		*tail = new_node;
		(*tail)->prev = temp;

		// new_node->next = (*tail)->next;
		// (*tail)->next = new_node;
		// *tail = new_node;
	}
}

// Percorre la lista e stampa i valori (attento alla condizione di uscita!)
void	print_list(t_node *tail)
{
	t_node	*start;
	int		id;

	start = tail;
	if (tail == NULL)
		return ;
	while (1)
	{
		tail = tail->next;
		id = tail->data.coder_id;
		printf("coder: %d prev: %p curr: %p next: %p\n", id, tail->prev, tail, tail->next);
		if (tail == start)
			break ;
	}
	printf("\n\n");
}

// Libera la memoria dai nodi
void	node_clean(t_node *tail, int num_cod)
{
	t_node	*temp;
	int		i;

	i = 0;
	while (i < num_cod)
	{
		temp = tail;
		tail = (tail)->next;
		free(temp);
		i++;
	}
}
