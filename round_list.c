/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 14:47:48 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/01 16:15:13 by gcerrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_codex.h"

// Alloca la memoria per un nuovo nodo e lo inizializza
Node *create_node(t_coder new_coder)
{
	Node *coder_place;

	coder_place = malloc(sizeof(Node));
	if (!coder_place)
		return NULL;
	coder_place->data = new_coder;
	coder_place->next = NULL;
	return coder_place;
}

// Inserisce un nodo all'inizio (subito dopo la tail)
void insert_head(Node **tail, t_coder new_coder)
{
	Node *new_node;

	new_node = create_node(new_coder);
	if (*tail == NULL)
	{
		new_node->next = new_node;
		*tail = new_node;
	}
	else
	{
		new_node->next = (*tail)->next;
		(*tail)->next = new_node;
	}
}

// Inserisce un nodo alla fine (diventa la nuova tail)
void insert_tail(Node **tail, t_coder new_coder)
{
	Node *new_node;

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
		*tail = new_node;
	}
}

// Percorre la lista e stampa i valori (attento alla condizione di uscita!)
void print_list(Node *tail)
{
	Node *start;

	int id;
	start = tail;
	if (tail == NULL)
	return;
	while (1)
	{
		tail = tail->next;
		id = tail->data.coder_id;
		printf("coder: %d\n", id);
		if (tail == start)
			break;
	}
}
