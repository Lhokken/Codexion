/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:44:02 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/15 16:39:00 by gcerrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_codex.h"

void    wait_my_turn(t_node *table)
{
    while (1)
    {
        if (table->coder.data->coder_burnout)
            return ;
        pthread_mutex_lock(table->coder.data->med_lock);
        if (table->coder.coder_id == table->coder.data->priority) 
        {
            table->coder.data->priority
                 = (table->coder.data->priority + 1) % table->coder.data->number_of_coders;
            pthread_mutex_unlock(table->coder.data->med_lock);
            return ;
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
