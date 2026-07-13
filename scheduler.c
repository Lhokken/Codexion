/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:44:02 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/13 22:07:06 by gcerrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_codex.h"

static bool is_my_turn(t_node *table, t_dongle *dongle)
{
    if (table->coder.priority_score == dongle->next_turn)
        return (true);
    return (false);
}

void    wait_my_turn(t_node *table, t_dongle *dongle)
{
    while (1)
    {
        pthread_mutex_lock(table->coder.data->med_lock);
        bool is_burnout = table->coder.data->coder_burnout;
        pthread_mutex_unlock(table->coder.data->med_lock);
        pthread_mutex_lock(&dongle->lock);
        if (is_my_turn(table, dongle)) 
        {
            pthread_mutex_unlock(&dongle->lock);
            return ;
        }
        pthread_mutex_unlock(&dongle->lock);
        if (is_burnout)
            return ;
        usleep(1000);
    }
}

void    release_dongles(t_node *table)
{
    pthread_mutex_lock(&table->coder.left_dongle->lock);
    table->coder.left_dongle->next_turn = 
        (table->coder.left_dongle->next_turn + 1)
         % table->coder.data->number_of_coders;
    pthread_mutex_unlock(&table->coder.left_dongle->lock);
    pthread_mutex_lock(&table->coder.right_dongle->lock);
    table->coder.right_dongle->next_turn = 
        (table->coder.right_dongle->next_turn + 1)
         % table->coder.data->number_of_coders;
    pthread_mutex_unlock(&table->coder.right_dongle->lock);
    pthread_mutex_unlock(table->coder.left_dongle_lock);
    pthread_mutex_unlock(table->coder.right_dongle_lock);
}
