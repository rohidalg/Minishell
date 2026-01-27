/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 19:11:55 by wiljimen          #+#    #+#             */
/*   Updated: 2026/01/27 19:08:31 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	try_expand(char **out, const char *s, int *i, t_exp *e)
{
	if (s[*i] != '$' || e->q == '\'')
		return (0);
	if (s[*i + 1] == '?')
		return (*out = expansor_exit(*out, i, e->last), 1);
	if (is_var_start(s[*i + 1]))
		return (*out = expansor_var(*out, s, i, e->env), 1);
	return (0);
}

char	*expand_string(const char *s, char **env, int last)
{
	t_exp	e;
	char	*out;
	int		i;

	e.env = env;
	e.last = last;
	e.q = 0;
	out = ft_strdup("");
	i = 0;
	while (s && s[i])
	{
		if (try_expand(&out, s, &i, &e))
			continue ;
		if ((s[i] == '\'' || s[i] == '"') && e.q == 0)
			e.q = s[i++];
		else if (e.q && s[i] == e.q)
			e.q = 0, i++;
		else
			out = append_char(out, s[i++]);
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
