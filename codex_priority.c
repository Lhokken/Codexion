/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codex_priority.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:44:02 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/07 23:06:09 by gcerrete         ###   ########.fr       */
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

unsigned long long	get_time(struct timeval tv)
{
	return (((unsigned long long)tv.tv_sec * 1000) + \
		((unsigned long long)tv.tv_usec / 1000));
}
