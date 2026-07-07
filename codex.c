/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:44:02 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/07 23:12:37 by gcerrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_codex.h"

void	*working_steps(void *tabl)
{
	t_node	*table;

	table = (t_node *)tabl;
	while (table->coder.number_of_compiles_required > 0)
	{
		compile(table);
		debug(table);
		refactor(table);
		cooldown(table);
	}
	return (NULL);
}

void	working_flow(t_node *table)
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

void	table_generator(
	t_node **table,
	t_data data,
	pthread_mutex_t *dongle_lock
)
{
	int		i;
	t_coder	coder;

	i = 0;
	while (i < data.number_of_coders)
	{
		coder = coder_gen(data, i);
		pthread_mutex_init(&dongle_lock[i], NULL);
		coder.right_dongle_lock = &dongle_lock[i];
		coder.coder_id = i;
		insert_tail(table, coder);
		(*table)->coder.left_dongle = (*table)->prev->coder.right_dongle;
		(*table)->coder.left_dongle_lock = \
			(*table)->prev->coder.right_dongle_lock;
		i++;
	}
	(*table)->next->coder.left_dongle = (*table)->coder.right_dongle;
	(*table)->next->coder.left_dongle_lock = \
		(*table)->coder.right_dongle_lock;
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_node			*table;
	pthread_mutex_t	*dongle_lock;
	struct timeval	now;

	table = NULL;
	if (argc == 9)
	{
		data = data_inizialize();
		data = data_define(data, argv);
		dongle_lock = malloc(sizeof(pthread_mutex_t) * data.number_of_coders);
		gettimeofday(&now, NULL);
		data.start_time = get_time(now);
		table_generator(&table, data, dongle_lock);
		working_flow(table);
		node_clean(table, data.number_of_coders);
		free(dongle_lock);
	}
	else
		printf("\nRequired exactly 8 arguments\n\n");
}
