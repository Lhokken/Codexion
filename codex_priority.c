/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codex_priority.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:44:02 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/07 15:07:30 by gcerrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_codex.h"

void assign_priority_score(t_coder *coder, t_data *data)
{
    if (data->scheduler == "fifo")
    {
        coder->priority_score = data->global_ticket_dispenser;
        data->global_ticket_dispenser++;
    }
    else if (data->scheduler == "edf")
    {
        coder->priority_score = coder->time_to_compile + data->time_to_burnout;
    }
}

unsigned long long get_time_in_ms(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((unsigned long long)tv.tv_sec * 1000) + ((unsigned long long)tv.tv_usec / 1000);
}

