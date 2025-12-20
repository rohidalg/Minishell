/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 14:50:42 by will23            #+#    #+#             */
/*   Updated: 2025/12/20 17:26:07 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Devuelve una copia del nombre antes de '='
// "PATH=/usr/bin" -> "PATH"

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

// Devuelve una copia del valor después de '='
// "PATH=/usr/bin" -> "/usr/bin"

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

// Crea un nodo t_vars a partir de una línea del env: "NAME=VALUE"

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

// Añade un nodo al final de la lista vars

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

// Crea la lista t_vars a partir de g_env (char **)

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
