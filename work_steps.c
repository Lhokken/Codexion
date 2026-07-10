/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_steps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:44:02 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/10 18:30:13 by gcerrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_codex.h"

void	codex_print(t_node *table, char *message)
{
	long	time;
	int		id;

	pthread_mutex_lock(table->print_lock);
	pthread_mutex_lock(table->coder.data->med_lock);
	time = table->coder.total_time;
	id = table->coder.coder_id;
	printf("%ld\t%d %s\n", time, id + 1, message);
	pthread_mutex_unlock(table->print_lock);
	pthread_mutex_unlock(table->coder.data->med_lock);
}

static void	coder_awake_set(t_node *table, struct timeval now)
{
	table->coder.right_dongle->awake = (get_time (now)
			+ table->coder.data->time_to_compile
			+ table->coder.data->dongle_cooldown);
	table->coder.left_dongle->awake = (get_time (now)
			+ table->coder.data->time_to_compile
			+ table->coder.data->dongle_cooldown);
}

void	compile(t_node *table)
{
	struct timeval	now;
	bool			dead;

	pthread_mutex_lock(table->coder.data->med_lock);
	dead = table->coder.data->coder_burnout;
	pthread_mutex_unlock(table->coder.data->med_lock);
	if (dead)
	{
		table->coder.number_of_compiles_required = 0;
		return ;
	}
	compile_dongle_lock(table);
	gettimeofday(&now, NULL);
	codex_print(table, " is compiling");
	pthread_mutex_lock(table->coder.data->med_lock);
	table->coder.total_time = get_time(now) - table->coder.data->start_time;
	table->coder.last_compile = get_time(now);
	pthread_mutex_unlock(table->coder.data->med_lock);
	coder_awake_set(table, now);
	// table->coder.right_dongle->awake = (get_time (now)
	// 		+ table->coder.data->time_to_compile
	// 		+ table->coder.data->dongle_cooldown);
	// table->coder.left_dongle->awake = (get_time (now)
	// 		+ table->coder.data->time_to_compile
	// 		+ table->coder.data->dongle_cooldown);
	if (time_usleep(table->coder.time_to_compile, table))
	{
		pthread_mutex_unlock(table->coder.left_dongle_lock);
		pthread_mutex_unlock(table->coder.right_dongle_lock);
		return ;
	}
	pthread_mutex_unlock(table->coder.left_dongle_lock);
	pthread_mutex_unlock(table->coder.right_dongle_lock);
}

void	debug(t_node *table)
{
	struct timeval	now;
	bool			dead;

	pthread_mutex_lock(table->coder.data->med_lock);
	dead = table->coder.data->coder_burnout;
	pthread_mutex_unlock(table->coder.data->med_lock);
	if (dead)
	{
		table->coder.number_of_compiles_required = 0;
		return ;
	}
	gettimeofday(&now, NULL);
	if (time_usleep(table->coder.time_to_debug, table))
		return ;
	pthread_mutex_lock(table->coder.data->med_lock);
	table->coder.total_time = get_time(now) - table->coder.data->start_time;
	pthread_mutex_unlock(table->coder.data->med_lock);
	codex_print(table, " is debugging");
}

void	refactor(t_node *table)
{
	struct timeval	now;
	bool			dead;

	pthread_mutex_lock(table->coder.data->med_lock);
	dead = table->coder.data->coder_burnout;
	pthread_mutex_unlock(table->coder.data->med_lock);
	if (dead)
	{
		table->coder.number_of_compiles_required = 0;
		return ;
	}
	gettimeofday(&now, NULL);
	if (time_usleep(table->coder.time_to_refactor, table))
		return ;
	pthread_mutex_lock(table->coder.data->med_lock);
	table->coder.total_time = get_time(now) - table->coder.data->start_time;
	pthread_mutex_unlock(table->coder.data->med_lock);
	codex_print(table, " is refactoring");
	table->coder.number_of_compiles_required -= 1;
}
