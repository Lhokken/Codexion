/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inizialize_codex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:44:02 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/15 17:29:08 by gcerrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_codex.h"

t_data	*data_inizialize(t_data	*data)
{
	data->number_of_coders = 0;
	data->time_to_burnout = 0;
	data->time_to_compile = 0;
	data->time_to_debug = 0;
	data->time_to_refactor = 0;
	data->number_of_compiles_required = 0;
	data->dongle_cooldown = 0;
	data->scheduler = "none";
	return (data);
}

t_data	*data_define(t_data *data, char **argv)
{
	data->number_of_coders = atoi(argv[1]);
	data->time_to_burnout = atoi(argv[2]);
	data->time_to_compile = atoi(argv[3]);
	data->time_to_debug = atoi(argv[4]);
	data->time_to_refactor = atoi(argv[5]);
	data->number_of_compiles_required = atoi(argv[6]);
	data->dongle_cooldown = atoi(argv[7]);
	data->scheduler = argv[8];
	data->coder_burnout = false;
	data->med_lock = malloc(sizeof(pthread_mutex_t));
	if (!data->med_lock)
		return (NULL);
	memset(data->med_lock, 0, sizeof(pthread_mutex_t));
	pthread_mutex_init(data->med_lock, NULL);
	return (data);
}

void	data_print(t_data *data)
{
	printf("number_of_coders %d\n", data->number_of_coders);
	printf("time_to_burnout %d\n", data->time_to_burnout);
	printf("time_to_compile %d\n", data->time_to_compile);
	printf("time_to_debug %d\n", data->time_to_debug);
	printf("time_to_refactor %d\n", data->time_to_refactor);
	printf("number_of_compiles_required %d\n",
		data->number_of_compiles_required);
	printf("dongle_cooldown %d\n", data->dongle_cooldown);
	printf("scheduler %s\n", data->scheduler);
	printf("\n");
}

void	table_generator(
	t_node **table,
	t_data *data,
	pthread_mutex_t *dongle_lock
)
{
	int		i;
	t_coder	coder;
	t_node	*temp;

	i = 0;
	while (i < data->number_of_coders)
	{
		coder = coder_gen(data, i);
		pthread_mutex_init(&dongle_lock[i], NULL);
		coder.right_dongle_lock = &dongle_lock[i];
		insert_tail(table, coder);
		i++;
	}
	temp = *table;
	i = 0;
	while (i++ < data->number_of_coders)
	{
		temp->next->coder.left_dongle = temp->coder.right_dongle;
		temp->next->coder.left_dongle_lock = temp->coder.right_dongle_lock;
		temp = temp->next;
	}
}
