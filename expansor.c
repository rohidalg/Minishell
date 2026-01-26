/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 19:11:55 by wiljimen          #+#    #+#             */
/*   Updated: 2026/01/26 19:24:19 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_quote_state(char c, char *q)
{
	if (*q == 0 && (c == '\'' || c == '"'))
		*q = c;
	else if (*q != 0 && c == *q)
		*q = 0;
}

static int	is_quote_char(char c)
{
	return (c == '\'' || c == '"');
}

static int	try_expand(char **out, const char *s, int *i, char **env, int last, char q)
{
	if (s[*i] != '$' || q == '\'')
		return (0);
	if (s[*i + 1] == '?')
		return (*out = exp_exit(*out, i, last), 1);
	if (is_var_start(s[*i + 1]))
		return (*out = exp_var(*out, s, i, env), 1);
	return (0);
}

char	*expand_string(const char *s, char **env, int last)
{
	char	q;
	char	*out;
	int		i;

	q = 0;
	out = ft_strdup("");
	i = 0;
	while (s && s[i])
	{
		if (try_expand(&out, s, &i, env, last, q))
			continue ;
		if (is_quote_char(s[i]))
		{
			update_quote_state(s[i], &q);
			i++;
			continue ;
		}
		out = append_char(out, s[i]);
		i++;
	}
	return (out);
}

void	expand_args(char **args, char **env, int last)
{
	int		i;
	char	*tmp;

	i = 0;
	while (args && args[i])
	{
		tmp = expand_string(args[i], env, last);
		free(args[i]);
		args[i] = tmp;
		i++;
	}
}
