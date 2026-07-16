/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_steps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:44:02 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/16 23:10:46 by gcerrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_codex.h"

void	codex_print(t_node *table, char *message)
{
	long			time;
	int				id;

	pthread_mutex_lock(table->print_lock);
	pthread_mutex_lock(table->coder.data->med_lock);
	time = get_time() - table->coder.data->start_time;
	id = table->coder.coder_id;
	if (strcmp(message, " is burnout") == 0)
		printf("%ld\t%d %s\n", time, id + 1, message);
	if (table->coder.data->coder_burnout)
	{
		pthread_mutex_unlock(table->print_lock);
		pthread_mutex_unlock(table->coder.data->med_lock);
		return ;
	}
	printf("%ld\t%d %s\n", time, id + 1, message);
	pthread_mutex_unlock(table->print_lock);
	pthread_mutex_unlock(table->coder.data->med_lock);
}

static void	coder_awake_set(t_node *table)
{
	pthread_mutex_lock(table->coder.right_dongle_lock);
	table->coder.right_dongle->awake = (get_time()
			+ table->coder.data->time_to_compile
			+ table->coder.data->dongle_cooldown);
	pthread_mutex_unlock(table->coder.right_dongle_lock);
	pthread_mutex_lock(table->coder.left_dongle_lock);
	table->coder.left_dongle->awake = (get_time()
			+ table->coder.data->time_to_compile
			+ table->coder.data->dongle_cooldown);
	pthread_mutex_unlock(table->coder.left_dongle_lock);
}

void	compile(t_node *table)
{
	pthread_mutex_lock(table->coder.data->med_lock);
	if (table->coder.data->number_of_coders == 1)
	{
		pthread_mutex_unlock(table->coder.data->med_lock);
		return ;
	}
	if (table->coder.data->coder_burnout)
	{
		table->coder.number_of_compiles_required = 0;
		pthread_mutex_unlock(table->coder.data->med_lock);
		return ;
	}
	pthread_mutex_unlock(table->coder.data->med_lock);
	wait_my_turn(table, table->coder.data->number_of_coders);
	compile_dongle_lock(table);
	pthread_mutex_lock(table->coder.data->med_lock);
	table->coder.last_compile = get_time();
	pthread_mutex_unlock(table->coder.data->med_lock);
	codex_print(table, " is compiling");
	if (time_usleep(table->coder.time_to_compile, table))
		return ;
	coder_awake_set(table);
}

void	debug(t_node *table)
{
	bool			dead;

	pthread_mutex_lock(table->coder.data->med_lock);
	dead = table->coder.data->coder_burnout;
	pthread_mutex_unlock(table->coder.data->med_lock);
	codex_print(table, " is debugging");
	if (dead)
	{
		pthread_mutex_lock(table->coder.data->med_lock);
		table->coder.number_of_compiles_required = 0;
		pthread_mutex_unlock(table->coder.data->med_lock);
		return ;
	}
	if (time_usleep(table->coder.time_to_debug, table))
		return ;
}

void	refactor(t_node *table)
{
	bool			dead;

	pthread_mutex_lock(table->coder.data->med_lock);
	dead = table->coder.data->coder_burnout;
	pthread_mutex_unlock(table->coder.data->med_lock);
	codex_print(table, " is refactoring");
	if (dead)
	{
		pthread_mutex_lock(table->coder.data->med_lock);
		table->coder.number_of_compiles_required = 0;
		pthread_mutex_unlock(table->coder.data->med_lock);
		return ;
	}
	if (time_usleep(table->coder.time_to_refactor, table))
		return ;
	pthread_mutex_lock(table->coder.data->med_lock);
	table->coder.number_of_compiles_required -= 1;
	pthread_mutex_unlock(table->coder.data->med_lock);
}
