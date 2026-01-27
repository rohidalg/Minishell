/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:47:01 by rohidalg          #+#    #+#             */
/*   Updated: 2026/01/27 19:54:56 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_quote(char c, char *q)
{
	if (*q == 0 && (c == '\'' || c == '"'))
		*q = c;
	else if (*q == c)
		*q = 0;
}

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
			fprintf(stderr, "Error: '%c'\n", str[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

char	*remove_quotes(const char *s)
{
	size_t	i;
	size_t	j;
	char	q;
	char	*res;

	if (!s)
		return (NULL);
	res = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	q = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '"') && (q == 0 || q == s[i]))
			update_quote(s[i], &q);
		else
			res[j++] = s[i];
		i++;
	}
	return (res);
}
