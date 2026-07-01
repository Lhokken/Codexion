/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:44:02 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/01 17:36:07 by gcerrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_codex.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_coder	coder1;
	t_node	*table;
	int		i;

	i = 2;
	data = data_inizialize();
	coder1.coder_id = 1;
	table = NULL;
	if (argc == 9)
	{
		data = data_define(data, argv);
		data_print(data);
		insert_head(&table, coder1);
		while (i <= data.number_of_coders)
		{
			insert_tail(&table, coder1);
			table->data.coder_id = i;
			i++;
		}
	}
	else
		printf("\nRequired exactly 8 arguments\n\n");
	print_list(table);
	node_clean(table, data.number_of_coders);
}
