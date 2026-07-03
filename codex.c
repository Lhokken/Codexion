/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:44:02 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/03 19:43:30 by gcerrete         ###   ########.fr       */
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

void working_steps(t_node *table, t_data data)
{
	compile(table, data);
	debug(table);
	refactor(table);
}

void working_flow(t_node *table, t_data data)
{
	int check;

	check = data.number_of_coders;
	while (check > 0)
	{
		
		if (table->coder.number_of_compiles_required > 0)
		working_steps(table, data);
		else
		check -= 1;
		table = table->next;
		// printf("coder: %d left: %p right: %p\n",
		// id, table->coder.left_dongle, table->coder.right_dongle);

		// check = check_work(table);
	}
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_coder			coder;
	t_node			*table;
	int				i;

	i = 2;
	data = data_inizialize();
	coder = coder_gen(data, 1);
	table = NULL;
	insert_head(&table, coder);
	if (argc == 9)
	{
		data = data_define(data, argv);
		data_print(data);
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
	print_list(table);

	working_flow(table, data);
	node_clean(table, data.number_of_coders);
}
