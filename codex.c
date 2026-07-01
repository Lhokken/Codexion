/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:44:02 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/01 14:23:09 by gcerrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_codex.h"

Node	**table_inizialize(int number_of_coders, Node **table)
{
	t_coder *new_coder;
	int i;
	int j;

	i = 1;
	j = 0;
	printf("%d", number_of_coders);
	while(i <= number_of_coders)
	{

		new_coder = malloc(sizeof(t_coder));
		new_coder->coder_id = number_of_coders;
		insert_tail(table, *new_coder);
		printf("\ntest1: %d\n\n", i);
		j = (*table)->data.coder_id;
		printf("\ntest1: %d\n\n", j);
		i++;
	}
	return table;
}

int	main(int argc, char **argv)
{
	t_data data;
	Node **table;

	data = data_inizialize();
	table = NULL;
	if (argc == 9)
	{
		data = data_define(data, argv);
		data_print(data);
		
		table = table_inizialize(data.number_of_coders, table);

		print_list(table);
		
	}
	else
		printf("\nRequired exactly 8 arguments\n\n");
	
	
		
}
