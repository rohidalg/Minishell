/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_built.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 03:53:40 by wiljimen          #+#    #+#             */
/*   Updated: 2026/01/19 16:40:35 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_var_name(char *var)
{
	int	i;

	i = 1;
	if (!var || !var[0])
		return (0);
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}


int	find_var(char *var_to_see, t_vars *vars_list)
{
	t_vars	*tmp;
	char	*var_name;
	char	*var_value;
	
	if (!vars_list || !var_to_see)
		return (0);
	var_name = get_var_name(var_to_see);
	var_value = get_var_value(var_to_see);
	if (!var_name)
		return (free(var_name), 0);
	tmp = vars_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, var_name) == 0)
		{
			free(tmp->value);
			tmp->value = var_value;
			free(var_name);
			return (1);
		}
		tmp = tmp->next;
	}
	free(var_name);
	if (var_value)
		free(var_value);
	return (0);
}

void	vars_add_new(char *arg, t_vars **vars)
{
	t_vars	*new;

	if (!arg || !vars)
		return ;
	new = malloc(sizeof(t_vars));
	if (!new)
		return ;
	new->name = get_var_name(arg);
	if (!new->name)
	{
		free(new);
		return ;
	}
	new->value = get_var_value(arg);
	new->next = NULL;
	vars_add_back(vars, new);
}

static char	**export_one(char *arg, t_vars **vars, char **g_env)
{
	char	*name;

	name = get_var_name(arg);
	if (!name || !valid_var_name(name))
	{
		printf("minishell: export: `%s`: not a valid identifier\n", arg);
		free(name);
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

	if (!args || !args[1])
	{
		print_exported(*vars);
		return (g_env);
	}
	i = 1;
	while (args[i])
	{
		g_env = export_one(args[i], vars, g_env);
		i++;
	}
	return (g_env);
}
