/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_steps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:44:02 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/15 13:39:36 by gcerrete         ###   ########.fr       */
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
	table->coder.right_dongle->awake = (get_time()
			+ table->coder.data->time_to_compile
			+ table->coder.data->dongle_cooldown);
	table->coder.left_dongle->awake = (get_time()
			+ table->coder.data->time_to_compile
			+ table->coder.data->dongle_cooldown);
}

void	compile(t_node *table)
{
	pthread_mutex_lock(table->coder.data->med_lock);
	if (table->coder.data->number_of_coders == 1)
		return ;
	if (table->coder.data->coder_burnout)
	{
		table->coder.number_of_compiles_required = 0;
		return ;
	}
	pthread_mutex_unlock(table->coder.data->med_lock);
	
	// wait_my_turn(table);
    // wait_my_turn(table, table->coder.left_dongle);
	compile_dongle_lock(table);
	
	pthread_mutex_lock(table->coder.data->med_lock);
	table->coder.total_time = get_time() - table->coder.data->start_time;
	table->coder.last_compile = get_time();
	pthread_mutex_unlock(table->coder.data->med_lock);
	
	codex_print(table, " is compiling");
	coder_awake_set(table);
	pthread_mutex_unlock(table->coder.left_dongle_lock);
    pthread_mutex_unlock(table->coder.right_dongle_lock);
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
		table->coder.number_of_compiles_required = 0;
		return ;
	}
	if (time_usleep(table->coder.time_to_debug, table))
		return ;
	pthread_mutex_lock(table->coder.data->med_lock);
	table->coder.total_time = get_time() - table->coder.data->start_time;
	pthread_mutex_unlock(table->coder.data->med_lock);
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
		table->coder.number_of_compiles_required = 0;
		return ;
	}
	if (time_usleep(table->coder.time_to_refactor, table))
		return ;
	pthread_mutex_lock(table->coder.data->med_lock);
	table->coder.total_time = get_time() - table->coder.data->start_time;
	pthread_mutex_unlock(table->coder.data->med_lock);
	table->coder.number_of_compiles_required -= 1;
}
