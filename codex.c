/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:44:02 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/02 00:14:10 by gcerrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_codex.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_coder	coder;
	t_node	*table;
	int		i;

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
		printf("---- %d --- %p\n\n", table->coder.coder_id, coder.right_dongle);
		table->next->coder.left_dongle = coder.right_dongle;
	}

	else
		printf("\nRequired exactly 8 arguments\n\n");
	print_list(table);
	node_clean(table, data.number_of_coders);
}
