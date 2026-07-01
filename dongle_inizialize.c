/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_inizialize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcerrete <gcerrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 14:47:48 by gcerrete          #+#    #+#             */
/*   Updated: 2026/07/01 18:49:47 by gcerrete         ###   ########.fr       */
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
	while(dongle[i])
	{
		dongle[i] = "a";
		i++;
	}
	return (dongle);
}
