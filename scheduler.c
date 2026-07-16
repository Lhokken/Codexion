/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:04:00 by  gcerrete         #+#    #+#             */
/*   Updated: 2026/07/16 19:17:05 by gcerrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_codex.h"

static bool	check_burnout(t_data *data)
{
	bool	status;

	pthread_mutex_lock(data->med_lock);
	status = data->coder_burnout;
	pthread_mutex_unlock(data->med_lock);
	return (status);
}

// bool	edf_turn_choice(t_node *table)
// {
// 	return (true);
// }

void	wait_my_turn(t_node *table)
{
	while (1)
	{
		if (check_burnout(table->coder.data))
			return ;
		pthread_mutex_lock(table->coder.data->med_lock);
		if (strcmp(table->coder.data->scheduler, "fifo") == 0
			&& table->coder.coder_id == table->coder.data->priority)
		{
			table->coder.data->priority
				= (table->coder.data->priority + 1)
				% table->coder.data->number_of_coders;
			pthread_mutex_unlock(table->coder.data->med_lock);
			return ;
		}
		else
		{
			table->coder.wait_turn = true;
			if (table->coder.coder_id == table->coder.data->edf_coder_id)
			{
				table->coder.wait_turn = false;
				pthread_mutex_unlock(table->coder.data->med_lock);
				return ;
			}
		}
		pthread_mutex_unlock(table->coder.data->med_lock);
		usleep(1000);
	}
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
		pthread_mutex_unlock(table->coder.left_dongle_lock);
		pthread_mutex_unlock(table->coder.right_dongle_lock);
	}
	else
	{
		pthread_mutex_lock(table->coder.left_dongle_lock);
		codex_print(table, " has taken a dongle");
		usleep(cooldown_check(table->coder.left_dongle->awake) * 1000);
		pthread_mutex_lock(table->coder.right_dongle_lock);
		codex_print(table, " has taken a dongle");
		usleep(cooldown_check(table->coder.right_dongle->awake) * 1000);
		pthread_mutex_unlock(table->coder.right_dongle_lock);
		pthread_mutex_unlock(table->coder.left_dongle_lock);
	}
}
