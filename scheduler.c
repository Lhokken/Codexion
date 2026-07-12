/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:44:02 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/12 22:19:09 by gcerrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_codex.h"

void get_dongle(t_node *table, t_dongle *dongle)
{
    pthread_mutex_lock(&dongle->lock);
    while (
        dongle->is_taken == true ||
        dongle->next_turn != table->coder.coder_id ||
        get_time() < dongle->awake)
    {
        pthread_cond_wait(&dongle->cond, &dongle->lock);
        pthread_mutex_lock(table->coder.data->med_lock);
        if (table->coder.data->coder_burnout)
        {
            pthread_mutex_unlock(table->coder.data->med_lock);
            pthread_mutex_unlock(&dongle->lock);
            return;
        }
        pthread_mutex_unlock(table->coder.data->med_lock);
    }
    dongle->is_taken = true;
    pthread_mutex_unlock(&dongle->lock);
}

void free_dongle(t_node *table, t_dongle *dongle)
{
    pthread_mutex_lock(&dongle->lock);
    
    dongle->is_taken = false;
    
    // Passa il turno all'altro coder (assumendo che gli ID siano 0 e 1)
    // Se hai ID arbitrari, ti basta conoscere l'ID dell'altro coder
    dongle->next_turn = (table->coder.coder_id == 0) ? 1 : 0;
    
    pthread_cond_broadcast(&dongle->cond); // Risveglia l'altro
    pthread_mutex_unlock(&dongle->lock);
}