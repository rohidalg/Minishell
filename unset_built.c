/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:34:58 by wiljimen          #+#    #+#             */
/*   Updated: 2026/01/19 17:35:37 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_var_name(char *name)
{
	int	i;

	if (!name || !name[0])
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	var_same(char *var_name, char *name)
{
	int	i;

	i = 0;
	while (var_name[i] && var_name[i] != '=' && name[i])
	{
		if (var_name[i] != name[i])
			return (0);
		i++;
	}
	if ((var_name[i] == '=' || var_name[i] == '\0') && name[i] == '\0')
		return (1);
	return (0);
}

t_vars	*built_unset(t_vars *head, char *var_delete)
{
	t_vars	*previous;
	t_vars	*current;
	t_vars	*tmp;

	previous = NULL;
	current = head;
	while (current != NULL)
	{
		if (var_same(current->name, var_delete))
		{
			if (previous == NULL)
				head = current->next;
			else
				previous->next = current->next;
			tmp = current;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			break ;
		}
		previous = current;
		current = current->next;
	}
	return (head);
}

void	unset_var_from_array(char **array, char *var_delete)
{
	int	i;
	int	j;

	if (!array || !var_delete)
		return ;
	i = 0;
	while (array[i])
	{
		if (var_same(array[i], var_delete))
		{
			free(array[i]);
			j = i;
			while (array[j + 1])
			{
				array[j] = array[j + 1];
				j++;
			}
			array[j] = NULL;
			break ;
		}
		i++;
	}
}

// args = ["unset", "HOME", "PATH", NULL]

t_vars	*builtin_unset(char **args, t_vars *vars, char **g_env)
{
	int	i;
	int	status;

	status = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_var_name(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			status = 1;
		}
		else
		{
			unset_var_from_array(g_env, args[i]);
			vars = built_unset(vars, args[i]);
		}
		i++;
	}
	g_exit_status = status;
	return (vars);
}

// vars = built_unset(vars, "HOME");
