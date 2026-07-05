/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:44:02 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/05 21:23:02 by gcerrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_codex.h"

int	check_work(t_node *table)
{
	t_node	*start;
	int		check;

	check = 0;
	start = table;
	while (1)
	{
		table = table->next;
		check += table->coder.number_of_compiles_required;
		if (table == start)
		{
			break ;
		}
	}
	return check;
}

void *working_steps(void *tabl)
{
	t_node	*table;

	table = (t_node*)tabl;
	while (table->coder.number_of_compiles_required > 0)
	{
		compile(table);
		debug(table);
		refactor(table);
		cooldown(table);
	}
	return NULL;
}

void working_flow(t_node *table)
{
	t_node			*end;
	pthread_mutex_t	print_lock;

	end = table;
	table = table->next;
	pthread_mutex_init(&print_lock, NULL);
	while (1)
	{
		table->print_lock = &print_lock;
		pthread_create(&table->id_thread, NULL, working_steps, table);
		if (table == end)
			break ;
		table = table->next;
	}
	end = table;
	table = table->next;
	while (1)
	{
		pthread_join(table->id_thread, NULL);
		if (table == end)
			break ;
		table = table->next;
	}
	pthread_mutex_destroy(&print_lock);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_coder			coder;
	t_node			*table;
	int				i;

	i = 2;
	data = data_inizialize();
	data = data_define(data, argv);
	coder = coder_gen(data, 1);
	table = NULL;
	insert_head(&table, coder);
	if (argc == 9)
	{
		// data_print(data);
		while (i <= data.number_of_coders)
		{
			coder = coder_gen(data, i);
			coder.coder_id = i;
			insert_tail(&table, coder);
			table->coder.left_dongle = table->prev->coder.right_dongle;
			i++;
		}
		table->next->coder.left_dongle = coder.right_dongle;
	}
	else
		printf("\nRequired exactly 8 arguments\n\n");
	// print_list(table);
	working_flow(table);
	node_clean(table, data.number_of_coders);
}
