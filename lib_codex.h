/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_codex.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 17:07:38 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/15 18:30:01 by gcerrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_CODEX_H
# define LIB_CODEX_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <stdbool.h>

typedef struct s_data
{
	int					number_of_coders;
	int					time_to_burnout;
	int					time_to_compile;
	int					time_to_debug;
	int					time_to_refactor;
	int					number_of_compiles_required;
	int					dongle_cooldown;
	int					priority;
	int					edf_time;
	bool				coder_burnout;
	char				*scheduler;
	unsigned long long	start_time;
	pthread_mutex_t		*med_lock;
}	t_data;

typedef struct s_dongle
{
	int					next_turn;
	int					dongle_id;
	int					dongle_cooldown;
	unsigned long long	awake;
	char				*scheduler;
	pthread_mutex_t		lock;
	bool				is_taken;
}	t_dongle;

typedef struct s_coder
{
	int					coder_id;
	t_dongle			*right_dongle;
	t_dongle			*left_dongle;
	pthread_mutex_t		*right_dongle_lock;
	pthread_mutex_t		*left_dongle_lock;
	pthread_mutex_t		*lock;
	int					time_to_burnout;
	int					time_to_compile;
	int					time_to_debug;
	int					time_to_refactor;
	int					number_of_compiles_required;
	int					dongle_cooldown;
	int					priority_score;
	unsigned long long	total_time;
	unsigned long long	last_compile;
	struct timeval		start;
	struct timeval		end;
	t_data				*data;
}	t_coder;

typedef struct t_node
{
	t_coder			coder;
	pthread_t		id_thread;
	pthread_mutex_t	*print_lock;
	struct t_node	*next;
	struct t_node	*prev;
}	t_node;

t_node				*create_node(t_coder new_coder);
void				insert_head(t_node **tail, t_coder new_coder);
void				insert_tail(t_node **tail, t_coder new_coder);
void				print_list(t_node *tail);
void				node_clean(
						t_node *tail,
						t_data *data,
						pthread_mutex_t	*dongle_lock
						);
t_data				*data_inizialize(t_data *data);
t_data				*data_define(t_data *data, char **argv);
void				data_print(t_data *data);
t_coder				coder_gen(t_data *data, int id);
t_dongle			*dongle_create(t_data *data);
void				table_generator(
						t_node **table,
						t_data *data,
						pthread_mutex_t *dongle_lock
						);
void				codex_print(t_node *table, char *message);
void				compile(t_node *table);
void				debug(t_node *table);
void				refactor(t_node *table);
void				cooldown(t_node *table);
unsigned long long	get_time(void);
void				validate(char **argv);
void				compile_dongle_lock(t_node *table);
void				*med_coders(void *arg);
bool				time_usleep(int time_left, t_node *table);
void				wait_my_turn(t_node *table);
void				release_dongles(t_node *table);

#endif