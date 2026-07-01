/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_codex.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 17:07:38 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/01 23:19:08 by gcerrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_CODEX_H
# define LIB_CODEX_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_coder
{
	int		coder_id;
	char	*right_dongle;
	char	*left_dongle;
	int		time_to_burnout;
	int		time_to_compile;
	int		time_to_debug;
	int		time_to_refactor;
	int		number_of_compiles_required;
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
	struct t_node	*next;
	struct t_node	*prev;
}	t_node;

typedef struct s_data
{
	int		number_of_coders;
	int		time_to_burnout;
	int		time_to_compile;
	int		time_to_debug;
	int		time_to_refactor;
	int		number_of_compiles_required;
	int		dongle_cooldown;
	char	*scheduler;
}	t_data;

// Alloca la memoria per un nuovo nodo e lo inizializza
t_node	*create_node(t_coder new_coder);

// Inserisce un nodo all'inizio (subito dopo la tail)
void	insert_head(t_node **tail, t_coder new_coder);

// Inserisce un nodo alla fine (diventa la nuova tail)
void	insert_tail(t_node **tail, t_coder new_coder);

// Percorre la lista e stampa i valori (attento alla condizione di uscita!)
void	print_list(t_node *tail);
// Libera la memoria dei nodi
void	node_clean(t_node *tail, int num_cod);

t_data	data_inizialize(void);
t_data	data_define(t_data data, char **argv);
void	data_print(t_data data);
t_coder	coder_gen(t_data data, int id);
char	*dongle_create(void);

#endif