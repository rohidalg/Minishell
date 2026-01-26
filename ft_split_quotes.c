/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_comm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 18:11:30 by wiljimen          #+#    #+#             */
/*   Updated: 2026/01/26 18:16:00 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(const char *s)
{
	int		i;
	int		c;
	char	q;

	i = 0;
	c = 0;
	while (s && s[i])
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (!s[i])
			break ;
		c++;
		q = 0;
		while (s[i] && (q || (s[i] != ' ' && s[i] != '\t')))
		{
			if (!q && (s[i] == '\'' || s[i] == '"'))
				q = s[i];
			else if (q && s[i] == q)
				q = 0;
			i++;
		}
	}
	return (c);
}

static char	*next_word(const char *s, int *i)
{
	int		start;
	char	q;

	while (s[*i] == ' ' || s[*i] == '\t')
		(*i)++;
	start = *i;
	q = 0;
	while (s[*i] && (q || (s[*i] != ' ' && s[*i] != '\t')))
	{
		if (!q && (s[*i] == '\'' || s[*i] == '"'))
			q = s[*i];
		else if (q && s[*i] == q)
			q = 0;
		(*i)++;
	}
	return (ft_substr(s, start, *i - start));
}

char	**split_quote_aware(const char *s)
{
	char	**out;
	int		i;
	int		j;
	int		n;

	n = count_words(s);
	out = ft_calloc(n + 1, sizeof(char *));
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	while (j < n)
		out[j++] = next_word(s, &i);
	out[j] = NULL;
	return (out);
}
