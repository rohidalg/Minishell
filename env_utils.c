/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 08:18:28 by wiljimen          #+#    #+#             */
/*   Updated: 2026/01/19 16:40:29 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_replace(char *arg, char **g_env)
{
	int	i;
	int	var_len;

	if (!arg || !g_env)
		return (0);
	var_len = 0;
	while (arg[var_len] && arg[var_len] != '=')
		var_len++;
	i = 0;
	while (g_env[i])
	{
		if (ft_strncmp(g_env[i], arg, var_len) == 0
			&& g_env[i][var_len] == '='
			&& (arg[var_len] == '=' || arg[var_len] == '\0'))
		{
			free(g_env[i]);
			g_env[i] = ft_strdup(arg);
			return (1);
		}
		i++;
	}
	return (0);
}


char	**add_env_var(char *var, char **g_env)
{
	int		len;
	int		i;
	char	**new_env;
	
	len = 0;
	i = 0;
	while (g_env[len] != NULL)
		len++;
	new_env = ft_calloc(len + 2, sizeof(char *));
	if (!new_env)
		return (g_env);
	while (i < len)
	{
		new_env[i] = ft_strdup(g_env[i]);
		i++;
	}
	new_env[len] = ft_strdup(var);
	new_env[len + 1] = NULL;
	ft_free(g_env);
	return(new_env);
}

char	**env_set(char *arg, char **g_env)
{
	if (env_replace(arg, g_env))
		return (g_env);
	return (add_env_var(arg, g_env));
}

int	vars_set_if_exists(char *arg, t_vars *vars)
{
	t_vars	*node;
	char	*name;
	char	*value;

	name = get_var_name(arg);
	if (!name)
		return (0);
	value = get_var_value(arg);
	node = vars_find(vars, name);
	free(name);
	if (!node)
	{
		free(value);
		return (0);
	}
	free(node->value);
	node->value = value;
	return (1);
}

void	vars_mark_exported(char *name, t_vars **vars)
{
	t_vars	*node;

	if (!name || !vars)
		return ;
	node = vars_find(*vars, name);
	if (node)
		return ;
	vars_add_new(name, vars);
}

