/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_check_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:52:32 by wiljimen          #+#    #+#             */
/*   Updated: 2026/01/29 14:56:58 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*safe_val(char *v)
{
	if (!v)
		return ("");
	return (v);
}

static char	*join_free_left(char *left, char *right)
{
	char	*out;

	out = ft_strjoin(left, right);
	free(left);
	return (out);
}

static char	*expand_dollar(const char *s, int start, int *i, char **env)
{
	int		v;
	char	*name;
	char	*prefix;
	char	*val;

	v = ++(*i);
	while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
		(*i)++;
	name = ft_substr(s, v, *i - v);
	val = (char *)ft_getenv(name, env);
	free(name);
	prefix = ft_substr(s, start, v - start - 1);
	return (join_free_left(prefix, safe_val(val)));
}

char	*expand_in_quotes(const char *s, char **env)
{
	int	i;
	int	start;

	i = 0;
	start = ++i;
	while (s[i] && s[i] != '"')
	{
		if (s[i] == '$')
			return (expand_dollar(s, start, &i, env));
		i++;
	}
	return (ft_substr(s, start, i - start));
}
