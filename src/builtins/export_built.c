/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_built.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 03:53:40 by wiljimen          #+#    #+#             */
/*   Updated: 2026/01/28 14:11:49 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**export_one(char *arg, t_vars **vars, char **g_env, int *err)
{
	char	*name;

	name = get_var_name(arg);
	if (!name || !valid_var_name(name))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		free(name);
		*err = 1;
		return (g_env);
	}
	if (ft_strchr(arg, '='))
	{
		if (!find_var(arg, *vars))
			vars_add_new(arg, vars);
		g_env = env_set(arg, g_env);
	}
	else
		vars_mark_exported(name, vars);
	free(name);
	return (g_env);
}

char	**builtin_export(char **args, t_vars **vars, char **g_env)
{
	int	i;
	int	err;

	if (!args || !args[1])
	{
		print_exported(*vars);
		g_exit_status = 0;
		return (g_env);
	}
	i = 1;
	err = 0;
	while (args[i])
	{
		g_env = export_one(args[i], vars, g_env, &err);
		i++;
	}
	g_exit_status = err;
	return (g_env);
}
