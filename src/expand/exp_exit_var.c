/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_exit_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 18:46:28 by wiljimen          #+#    #+#             */
/*   Updated: 2026/01/27 19:08:17 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*join_char(char *a, const char *b)
{
	char	*tmp;

	if (!b)
		return (a);
	if (!a)
		return (ft_strdup(b));
	tmp = ft_strjoin(a, b);
	free(a);
	return (tmp);
}

char	*append_char(char *s, char c)
{
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	return (join_char(s, buf));
}

char	*expansor_exit(char *out, int *i, int last)
{
	char	*tmp;

	tmp = ft_itoa(last);
	out = join_char(out, tmp);
	free(tmp);
	*i += 2;
	return (out);
}

char	*expansor_var(char *out, const char *s, int *i, char **g_env)
{
	int		len;
	char	*name;
	char	*val;

	len = var_name_len(s + (*i + 1));
	name = ft_substr(s, *i + 1, len);
	if (!name)
		return (out);
	val = (char *)ft_getenv(name, g_env);
	out = join_char(out, val);
	free(name);
	*i += 1 + len;
	return (out);
}

