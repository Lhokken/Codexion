/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:44:02 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/13 15:42:05 by gcerrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_codex.h"

void	*working_steps(void *tabl)
{
	t_node	*table;

	table = (t_node *)tabl;
	while (1)
	{
		if (table->coder.data->number_of_coders == 1)
			return (NULL);
		pthread_mutex_lock(table->coder.data->med_lock);
		if (table->coder.data->coder_burnout)
		{
			pthread_mutex_unlock(table->coder.data->med_lock);
			return (NULL);
		}
		pthread_mutex_unlock(table->coder.data->med_lock);
		if (table->coder.number_of_compiles_required <= 0)
			return (NULL);
		compile(table);
		debug(table);
		refactor(table);
	}
	return (NULL);
}

static void	print_lock_init(
	t_node *table,
	t_node *end,
	pthread_mutex_t	*print_lock)
{
	while (1)
	{
		table->print_lock = print_lock;
		pthread_create(&table->id_thread, NULL, working_steps, table);
		if (table == end)
			break ;
		table = table->next;
	}
}

void	working_flow(t_node *table)
{
	t_node			*end;
	pthread_mutex_t	print_lock;
	pthread_t		med_thread;

	if (table->coder.data->coder_burnout == true)
		return ;
	end = table;
	table = table->next;
	pthread_mutex_init(&print_lock, NULL);
	print_lock_init(table, end, &print_lock);
	pthread_create(&med_thread, NULL, med_coders, table);
	pthread_join(med_thread, NULL);
	while (1)
	{
		pthread_join(table->id_thread, NULL);
		if (table == end)
			break ;
		table = table->next;
	}
	pthread_mutex_destroy(&print_lock);
}

void	*med_coders(void *arg)
{
	t_node		*table;
	static int	i;

	table = (t_node *)arg;
	table = table->next;
	while (i < table->coder.data->number_of_coders)
	{
		pthread_mutex_lock(table->coder.data->med_lock);
		if ((int)(get_time() - table->coder.last_compile)
			> table->coder.data->time_to_burnout)
		{
			table->coder.data->coder_burnout = true;
			pthread_mutex_unlock(table->coder.data->med_lock);
			assign_priority_score(&table->coder, table->coder.data);
			codex_print(table, " is burnout");
			break ;
		}
		if (table->coder.number_of_compiles_required == 0)
			i++;
		pthread_mutex_unlock(table->coder.data->med_lock);
		usleep(100);
		table = table->next;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data			*data;
	t_node			*table;
	pthread_mutex_t	*dongle_lock;

	table = NULL;
	if (argc == 9)
	{
		validate(argv);
		data = malloc(sizeof(t_data));
		if (!data)
			return (0);
		memset(data, 0, sizeof(t_data));
		data = data_inizialize(data);
		data = data_define(data, argv);
		dongle_lock = malloc(sizeof(pthread_mutex_t) * data->number_of_coders);
		if (!dongle_lock)
			return (0);
		memset(dongle_lock, 0, sizeof(pthread_mutex_t));
		data->start_time = get_time();
		table_generator(&table, data, dongle_lock);
		working_flow(table);
		node_clean(table, data, dongle_lock);
		pthread_mutex_destroy(data->med_lock);
		free(data->med_lock);
		free(data);
	}
	else
		printf("\nRequired exactly 8 arguments\n\n");
}
