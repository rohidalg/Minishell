/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 20:26:05 by wiljimen          #+#    #+#             */
/*   Updated: 2026/01/26 19:07:05 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_var_start(char c)
{
	return (c == '_' || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int	is_var_char(char c)
{
	return (is_var_start(c) || (c >= '0' && c <= '9'));
}

int	var_name_len(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && is_var_char(s[i]))
		i++;
	return (i);
}

const char	*get_env_value(const char *var, char **g_env)
{
	int	i;
	int	n;
	
	n = (int)ft_strlen(var);
	i = 0;
	if (!var || g_env)
		return ("");
	while (g_env[i])
	{
		if (!ft_strncmp(g_env[i], var, n) && g_env[i][n] == '=')
			return (g_env[i] + n + 1);
		i++;
	}
	return ("");
}
