/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 14:50:42 by will23            #+#    #+#             */
/*   Updated: 2026/01/27 19:54:11 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_var_name(char *str)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

char	*get_var_value(char *str)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	return (ft_substr(str, i + 1, ft_strlen(str) - i - 1));
}

t_vars	*new_var_node(char *env_line)
{
	t_vars	*node;

	node = malloc(sizeof(t_vars));
	if (!node)
		return (NULL);
	node->name = get_var_name(env_line);
	node->value = get_var_value(env_line);
	if (!node->name || !node->value)
	{
		free(node->name);
		free(node->value);
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

void	vars_add_back(t_vars **head, t_vars *new)
{
	t_vars	*tmp;

	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_vars	*init_vars_from_env(char **g_env)
{
	int		i;
	t_vars	*vars;

	vars = NULL;
	if (!g_env)
		return (NULL);
	i = 0;
	while (g_env[i])
	{
		vars_add_back(&vars, new_var_node(g_env[i]));
		i++;
	}
	return (vars);
}
