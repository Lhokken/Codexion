/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codex_priority.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:44:02 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/15 16:38:10 by gcerrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_codex.h"

unsigned long long	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (((unsigned long long)now.tv_sec * 1000) + \
		((unsigned long long)now.tv_usec / 1000));
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
