/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:44:02 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/15 14:24:42 by gcerrete         ###   ########.fr       */
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

static void	validate_parameters(char **argv)
{
	int	i;

	i = 2;
	while (i <= 7)
	{
		if (i == 6)
		{
			if (atoi(argv[i]) < 1)
			{
				printf("At least 1 compile to do\n");
				exit (0);
			}
		}
		else
		{
			if (atoi(argv[i]) < 10)
			{
				printf("Parameter is too low\n");
				exit (0);
			}
		}
		i++;
	}
	// burn-com-deb-ref-N com-cool
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
	if (atoi(argv[i = 1]) == 0)
	{
		printf("Number of coders must be > 0\n");
		exit (0);
	}
	validate_parameters(argv);
}
