/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:44:02 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/10 17:37:17 by gcerrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_codex.h"

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	validate(char **argv)
{
	int	i;

	i = 1;
	while (i < 8)
	{
		if (is_digit(argv[i]) == 0)
		{
			printf("Argument must be an integer > 0\n");
			exit (0);
		}
		i++;
	}
	if ((strcmp(argv[i], "fifo") != 0) && (strcmp(argv[i], "edf") != 0))
	{
		printf("Scheduler must be 'fifo' or 'edf'\n");
		exit (0);
	}
}
