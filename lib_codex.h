/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_codex.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 17:07:38 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/07 22:32:35 by gcerrete         ###   ########.fr       */
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

typedef struct s_data
{
	int				number_of_coders;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				number_of_compiles_required;
	int				dongle_cooldown;
	unsigned long	global_ticket_dispenser;
	char			*scheduler;
	unsigned long	start_time;
}	t_data;

typedef struct s_coder
{
	int				coder_id;
	char			*right_dongle;
	char			*left_dongle;
	pthread_mutex_t	*right_dongle_lock;
	pthread_mutex_t	*left_dongle_lock;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				number_of_compiles_required;
	int				dongle_cooldown;
	unsigned long	priority_score;
	unsigned long	total_time;
	struct timeval	start;
	struct timeval	end;
	t_data			data;
}	t_coder;

typedef struct s_dongle
{
	int		dongle_id;
	int		dongle_cooldown;
	char	scheduler;
}	t_dongle;

typedef struct t_node
{
	t_coder			coder;
	pthread_t		id_thread;
	pthread_mutex_t	*print_lock;
	struct t_node	*next;
	struct t_node	*prev;
}	t_node;

// Alloca la memoria per un nuovo nodo e lo inizializza
t_node				*create_node(t_coder new_coder);

// Inserisce un nodo all'inizio (subito dopo la tail)
void				insert_head(t_node **tail, t_coder new_coder);

// Inserisce un nodo alla fine (diventa la nuova tail)
void				insert_tail(t_node **tail, t_coder new_coder);

// Percorre la lista e stampa i valori (attento alla condizione di uscita!)
void				print_list(t_node *tail);
// Libera la memoria dei nodi
void				node_clean(t_node *tail, int num_cod);

t_data				data_inizialize(void);
t_data				data_define(t_data data, char **argv);
void				data_print(t_data data);
t_coder				coder_gen(t_data data, int id);
char				*dongle_create(void);

void				compile(t_node *table);
void				debug(t_node *table);
void				refactor(t_node *table);
void				cooldown(t_node *table);
			
void				assign_priority_score(t_coder *coder, t_data *data);
unsigned long long get_time_in_ms(struct timeval tv);

#endif