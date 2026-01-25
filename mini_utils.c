/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:47:01 by rohidalg          #+#    #+#             */
/*   Updated: 2026/01/24 23:40:12 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_quote(char c, char *q)
{
	if (*q == 0 && (c == '\'' || c == '"'))
		*q = c;
	else if (*q == c)
		*q = 0;
}

int	invalid_input(char *str)
{
	int		i;
	char	q;

	i = 0;
	q = 0;
	while (str && str[i])
	{
		update_quote(str[i], &q);
		if (q == 0 && (str[i] == '\\' || str[i] == ';'))
		{
			fprintf(stderr, "Error: caracter no permitido '%c'\n", str[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
