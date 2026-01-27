/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:12:47 by wiljimen          #+#    #+#             */
/*   Updated: 2026/01/27 20:12:08 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_vars	*find_var_helper(t_vars *lst, char *name)
{
	while (lst)
	{
		if (ft_strcmp(lst->name, name) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

int	find_var(char *var_to_see, t_vars *vars_list)
{
	t_vars	*node;
	char	*name;
	char	*value;

	if (!vars_list || !var_to_see)
		return (0);
	name = get_var_name(var_to_see);
	value = get_var_value(var_to_see);
	if (!name)
		return (free(value), 0);
	node = vars_find(vars_list, name);
	if (!node)
		return (free(name), free(value), 0);
	free(node->value);
	node->value = value;
	free(name);
	return (1);
}

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
