/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_steps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:44:02 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/03 20:07:39 by gcerrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_codex.h"

void compile(t_node *table, t_data data)
{
	struct timeval	start;
	struct timeval	end;
	// int				i;
	long			t;

	// i = 0;
	gettimeofday(&start, NULL);
	usleep(data.time_to_compile);

	// while (table->coder.left_dongle[i])
	// 	table->coder.left_dongle[i++] += 1;
	// while (table->coder.right_dongle[i])
	// 	table->coder.right_dongle[i++] += 1;

	gettimeofday(&end, NULL);
	t = end.tv_usec - start.tv_usec;
	printf("%ld\t%d is compiling\n", t, table->coder.coder_id);
}

void debug(t_node *table)
{
	struct timeval	start;
	struct timeval	end;
	long			t;
	int				vr;
	
	vr = table->coder.time_to_debug;
	gettimeofday(&start, NULL);
	usleep(vr);
	gettimeofday(&end, NULL);
	t = end.tv_usec - start.tv_usec;
	printf("%ld\t%d is debugging\n", t, table->coder.coder_id);
}

void refactor(t_node *table)
{
	struct timeval	start;
	struct timeval	end;
	long			t;

	gettimeofday(&start, NULL);
	usleep(table->coder.time_to_refactor);
	gettimeofday(&end, NULL);
	t = end.tv_usec - start.tv_usec;
	printf("%ld\t%d is refactoring\n", t, table->coder.coder_id);
	table->coder.number_of_compiles_required -= 1;
}

void cooldown(t_data data)
{
	struct timeval	start;
	struct timeval	end;
	long			t;

	gettimeofday(&start, NULL);
	usleep(data.dongle_cooldown);
	gettimeofday(&end, NULL);
	t = end.tv_usec - start.tv_usec;
	printf("%ld\t dongle cooldown\n", t);
}

// 0 	1 has taken a dongle
// 1 	1 has taken a dongle
// 1 	1 is compiling
// 201	1 is debugging
// 401	1 is refactoring
// 402	2 has taken a dongle
// 403	2 has taken a dongle
// 403	2 is compiling
// 603	2 is debugging
// 803	2 is refactoring
// 1204	3 burned out