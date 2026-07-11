/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 14:47:48 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/11 11:27:07 by gcerrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_codex.h"

t_node	*create_node(t_coder new_coder)
{
	t_node	*coder_place;

	coder_place = malloc(sizeof(t_node));
	if (!coder_place)
		return (NULL);
	coder_place->coder = new_coder;
	coder_place->next = NULL;
	coder_place->prev = NULL;
	return (coder_place);
}

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

void	insert_tail(t_node **tail, t_coder new_coder)
{
	t_node	*new_node;
	t_node	*temp;

	new_node = create_node(new_coder);
	if (*tail == NULL)
	{
		new_node->next = new_node;
		new_node->prev = new_node;
		*tail = new_node;
	}
	else
	{
		new_node->next = (*tail)->next;
		(*tail)->next = new_node;
		temp = (*tail);
		*tail = new_node;
		(*tail)->prev = temp;
		new_node->next->prev = new_node;
	}
}

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
		id = tail->coder.coder_id;
		printf("coder: %d left: %p right: %p\n",
			id, tail->coder.left_dongle, tail->coder.right_dongle);
		if (tail == start)
			break ;
	}
	printf("\n\n");
}

void	node_clean(t_node *tail, t_data *data, pthread_mutex_t	*dongle_lock)
{
	t_node	*temp;
	int		i;

	i = 0;
	while (i < data->number_of_coders)
	{
		temp = tail;
		tail = (tail)->next;
		free(temp->coder.left_dongle);
		free(temp);
		i++;
	}
	i = 0;
	while (i < data->number_of_coders)
	{
		pthread_mutex_destroy(&dongle_lock[i]);
		i++;
	}
	free(dongle_lock);
}
