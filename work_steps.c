/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_steps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:44:02 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/07 22:49:23 by gcerrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_codex.h"

void codex_print(t_node *table, char *message)
{
	long	time;
	int		id;

	pthread_mutex_lock(table->print_lock);
	time = table->coder.total_time;
	id = table->coder.coder_id;
	printf("%ld\t%d %s\n", time, id, message);
	pthread_mutex_unlock(table->print_lock);
}

void compile(t_node *table)
{
	struct timeval now;
	int i;

	i = 0;
	gettimeofday(&now, NULL);
	if (table->coder.coder_id % 2 == 0)
	{
		pthread_mutex_lock(table->coder.right_dongle_lock);
		pthread_mutex_lock(table->coder.left_dongle_lock);
	}
	else
	{
		pthread_mutex_lock(table->coder.left_dongle_lock);
		pthread_mutex_lock(table->coder.right_dongle_lock);
	}
	while (table->coder.left_dongle[i])
	table->coder.left_dongle[i++] += 1;
	i = 0;
	while (table->coder.right_dongle[i])
	table->coder.right_dongle[i++] += 1;
	usleep(table->coder.time_to_compile * 1000);
	pthread_mutex_unlock(table->coder.left_dongle_lock);
	pthread_mutex_unlock(table->coder.right_dongle_lock);
	table->coder.total_time = get_time_in_ms(now) - table->coder.data.start_time;
	codex_print(table, " is compiling");
}

void debug(t_node *table)
{
	struct timeval now;
	
	gettimeofday(&now, NULL);
	usleep(table->coder.time_to_debug * 1000);

	table->coder.total_time = get_time_in_ms(now) - table->coder.data.start_time;
	codex_print(table, " is debugging");
}

void refactor(t_node *table)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	usleep(table->coder.time_to_refactor * 1000);

	table->coder.total_time = get_time_in_ms(now) - table->coder.data.start_time;
	codex_print(table, " is refactoring");
	table->coder.number_of_compiles_required -= 1;
}

void cooldown(t_node *table)
{
	struct timeval now;


	gettimeofday(&now, NULL);
	usleep(table->coder.dongle_cooldown * 1000);

	table->coder.total_time = get_time_in_ms(now) - table->coder.data.start_time;
	codex_print(table, " dongle cooldown");
}

// 0 	1 has taken a dongle
// 1 	1 has taken a dongle
// 1 	1 is compiling
// 201	1 is debugging
// 401	1 is refactoring
// 402	2 has taken a dongle
// 403	2 has taken a dongle
// 403	2 is compiling
// 603	2 is debugging
// 803	2 is refactoring
// 1204	3 burned out