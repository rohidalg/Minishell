/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_built.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 03:53:40 by wiljimen          #+#    #+#             */
/*   Updated: 2025/12/20 17:12:31 by wiljimen         ###   ########.fr       */
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

t_vars	*vars_find(t_vars *vars, char *name)
{
	while (vars)
	{
		if (ft_strcmp(vars->name, name) == 0)
			return (vars);
		vars = vars->next;
	}
	return (NULL);
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


char	**builtin_export(char **args, t_vars **vars_list, char **g_env)
{
	int		i;
	char	*name;

	i = 1;
	while(args && args[i])
	{
		name = get_var_name(args[i]);
		if (!name || !valid_var_name(name))
		{
			printf("Error bad var name\n");
			free(name);
			i++;
			continue ;
		}
		if (ft_strchr(args[i], '='))
		{
			if (!find_var(args[i], *vars_list))
				vars_add_new(args[i], vars_list);
			g_env = env_set(args[i], g_env);
		}
		else
			vars_mark_exported(name, vars_list);	
		free(name);
		i++;
	}
	return (g_env);
}
