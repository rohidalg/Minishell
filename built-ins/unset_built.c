/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:34:58 by wiljimen          #+#    #+#             */
/*   Updated: 2025/10/09 19:52:42 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_valid_var_name(char *name)
{
	int	i;

	i = 1;
	if (!name || (!ft_isalpha(name[0]) || name[0] != '_'))
		return (0);
	while (name[i])
	{
		if (!ft_isalnum(name[i]) || name[i] != '_')
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
			break;
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

t_vars	*builtin_unset(char **args, t_vars *vars, char **env, char **g_env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!is_valid_var_name(args[i]))
			printf("minishell: unset: `%s`: not a valid identifier\n", args[i]);
		else
		{
			unset_var_from_array(env, args[i]);
			unset_var_from_array(g_env, args[i]);
			vars = built_unset(vars, args[i]);
		}
		i++;
	}
	return (vars);
}

// vars = built_unset(vars, "HOME");


