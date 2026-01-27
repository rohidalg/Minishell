/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:13:36 by wiljimen          #+#    #+#             */
/*   Updated: 2026/01/27 19:07:06 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	vars_counter(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars)
	{
		i++;
		vars = vars->next;
	}
	return (i);
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

char	**vars_copy(t_vars *vars)
{
	char	**vars_names;
	int		i;
	int		vars_count;

	i = 0;
	vars_count = vars_counter(vars);
	vars_names = ft_calloc(vars_count + 1, sizeof(char *));
	if (!vars_names)
	{
		ft_free(vars_names);
		return (NULL);
	}
	while (vars)
	{
		vars_names[i] = ft_strdup(vars->name);
		vars = vars->next;
		i++;
	}
	vars_names[i] = NULL;
	return (vars_names);
}

void	sort_names(char **vars_names)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (vars_names[i])
	{
		j = i + 1;
		while (vars_names[j])
		{
			if (ft_strcmp(vars_names[i], vars_names[j]) > 0)
			{
				tmp = vars_names[i];
				vars_names[i] = vars_names[j];
				vars_names[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_exported(t_vars *vars_names)
{
	char	**names;
	int		i;
	t_vars	*node;

	names = vars_copy(vars_names);
	i = 0;
	if (!names)
		return ;
	sort_names(names);
	while (names[i])
	{
		node = vars_find(vars_names, names[i]);
		if (node->value)
			printf("declare -x %s=\"%s\"\n", node->name, node->value);
		else
			printf("declare -x %s\n", node->name);
		free(names[i]);
		i++;
	}
	free(names);
}
