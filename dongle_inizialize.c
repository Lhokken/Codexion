/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_inizialize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 14:47:48 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/01 23:26:17 by gcerrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_codex.h"

// Crea un dongle univoco.
char	*dongle_create(void)
{
	char	*dongle;
	int		i;

	dongle = malloc(10 * sizeof(char));
	i = 0;
	if (!dongle)
		return (NULL);
	while(i < 10)
	{
		dongle[i] = 'a';
		i++;
	}
	dongle[i] = '\0';
	return (dongle);
}

t_coder	coder_gen(t_data data, int id)
{
	t_coder	coder;

	coder.coder_id = id;
	coder.right_dongle = dongle_create();
	coder.number_of_compiles_required = data.number_of_compiles_required;
	coder.time_to_burnout = data.time_to_burnout;
	coder.time_to_compile = data.time_to_compile;
	coder.time_to_refactor = data.time_to_refactor;
	return (coder);
}
