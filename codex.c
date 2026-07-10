/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:44:02 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/10 14:58:19 by gcerrete         ###   ########.fr       */
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
	}
	return (NULL);
}

void	working_flow(t_node *table)
{
	t_node			*end;
	pthread_mutex_t	print_lock;
	pthread_t		med_thread;

	if (table->coder.data.coder_burnout == true)
		return;
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
	pthread_create(&med_thread, NULL, med_coders, table);
	table = table->next;
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
	t_node			*table;
	struct timeval	now;

	table = (t_node *)arg;
	table = table->next;
	while (1)
	{
		gettimeofday(&now, NULL);
		pthread_mutex_lock(table->coder.data.med_lock);
		// printf("last_comp: %i time_burn: %i\n", (int)(get_time(now) - table->coder.last_compile), table->coder.data.time_to_burnout);
		if ((int)(get_time(now) - table->coder.last_compile) > table->coder.data.time_to_burnout)
		{
			table->coder.data.coder_burnout = true;
			pthread_mutex_unlock(table->coder.data.med_lock);
			codex_print(table, " is burnout");
			break ;
		}
		pthread_mutex_unlock(table->coder.data.med_lock);
		usleep(100);
		table = table->next;
	}
	return NULL;
}

int	main(int argc, char **argv)
{
	t_data			*data;
	t_node			*table;
	pthread_mutex_t	*dongle_lock;
	struct timeval	now;

	table = NULL;
	if (argc == 9)
	{
		validate(argv);
		data = malloc(sizeof(t_data));
		data = data_inizialize(data);
		data = data_define(data, argv);
		dongle_lock = malloc(sizeof(pthread_mutex_t) * data->number_of_coders);
		gettimeofday(&now, NULL);
		data->start_time = get_time(now);
		table_generator(&table, data, dongle_lock);
		working_flow(table);
		node_clean(table, data->number_of_coders);
		free(dongle_lock);
		pthread_mutex_destroy(data->med_lock);
		free(data->med_lock);
	}
	else
		printf("\nRequired exactly 8 arguments\n\n");
}
