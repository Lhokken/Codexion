/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codex_priority.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:44:02 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/11 11:26:27 by gcerrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_codex.h"

void	assign_priority_score(t_coder *coder, t_data *data)
{
	if (strcmp(data->scheduler, "fifo") == 0)
	{
		coder->priority_score = data->global_ticket_dispenser;
		data->global_ticket_dispenser++;
	}
	else if (strcmp(data->scheduler, "edf") == 0)
	{
		coder->priority_score = coder->time_to_compile + data->time_to_burnout;
	}
	else
		printf("Scheduler input error");
}

unsigned long long	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (((unsigned long long)now.tv_sec * 1000) + \
		((unsigned long long)now.tv_usec / 1000));
}

static int	cooldown_check(unsigned long long available)
{
	if (available > get_time())
		return (available - get_time());
	else
		return (0);
}

void	compile_dongle_lock(t_node *table)
{
	if (table->coder.coder_id % 2 == 0)
	{
		pthread_mutex_lock(table->coder.right_dongle_lock);
		codex_print(table, " has taken a dongle");
		usleep(cooldown_check(table->coder.right_dongle->awake) * 1000);
		pthread_mutex_lock(table->coder.left_dongle_lock);
		codex_print(table, " has taken a dongle");
		usleep(cooldown_check(table->coder.left_dongle->awake) * 1000);
	}
	else
	{
		pthread_mutex_lock(table->coder.left_dongle_lock);
		codex_print(table, " has taken a dongle");
		usleep(cooldown_check(table->coder.left_dongle->awake) * 1000);
		pthread_mutex_lock(table->coder.right_dongle_lock);
		codex_print(table, " has taken a dongle");
		usleep(cooldown_check(table->coder.right_dongle->awake) * 1000);
	}
}

bool	time_usleep(int time_left, t_node *table)
{
	while (time_left > 0)
	{
		usleep(1000);
		time_left -= 1;
		pthread_mutex_lock(table->coder.data->med_lock);
		if (table->coder.data->coder_burnout)
		{
			pthread_mutex_unlock(table->coder.data->med_lock);
			return (true);
		}
		pthread_mutex_unlock(table->coder.data->med_lock);
	}
	return (false);
}
