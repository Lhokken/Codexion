/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_inizialize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 14:47:48 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/15 17:30:21 by gcerrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_codex.h"

t_dongle	*dongle_create(t_data *data)
{
	t_dongle	*dongle;

	dongle = malloc(sizeof(t_dongle));
	if (!dongle)
		return (NULL);
	pthread_mutex_init(&dongle->lock, NULL);
	dongle->awake = 0;
	dongle->dongle_cooldown = data->dongle_cooldown;
	dongle->scheduler = data->scheduler;
	dongle->next_turn = 0;
	return (dongle);
}

t_coder	coder_gen(t_data *data, int id)
{
	t_coder			coder;
	pthread_mutex_t	*lock;

	lock = malloc(sizeof(pthread_mutex_t));
	if (!lock)
		exit(EXIT_FAILURE);
	pthread_mutex_init(lock, NULL);
	coder.coder_id = id;
	coder.lock = lock;
	coder.priority_score = id;
	coder.right_dongle = dongle_create(data);
	coder.right_dongle->dongle_id = id;
	coder.number_of_compiles_required = data->number_of_compiles_required;
	coder.time_to_burnout = data->time_to_burnout;
	coder.time_to_compile = data->time_to_compile;
	coder.time_to_refactor = data->time_to_refactor;
	coder.time_to_debug = data->time_to_debug;
	coder.dongle_cooldown = data->dongle_cooldown;
	coder.last_compile = data->start_time;
	coder.total_time = 0;
	coder.data = data;
	return (coder);
}
