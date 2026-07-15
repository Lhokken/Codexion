/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:44:02 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/15 13:47:50 by gcerrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_codex.h"

void    wait_my_turn(t_node *table)
{
    while (1)
    {
        pthread_mutex_lock(table->coder.lock);
        if (table->coder.coder_id == table->coder.data->priority) 
        {
            table->coder.data->priority
                 = (table->coder.data->priority + 1) % table->coder.data->number_of_coders;
            pthread_mutex_unlock(table->coder.lock);
            return ;
        }
        pthread_mutex_unlock(table->coder.lock);
        // if (is_burnout)
        //     return ;
        usleep(1000);
    }
}

