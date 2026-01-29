/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_helper_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:52:01 by wiljimen          #+#    #+#             */
/*   Updated: 2026/01/29 17:02:42 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	insert_split_token(char ***args, int i, char *op, char *rest)
{
	char	**new;
	int		n;
	int		j;

	n = count_args(*args);
	new = ft_calloc(n + 2, sizeof(char *));
	if (!new)
		return (free(op), free(rest), 0);
	j = 0;
	while (j < i)
	{
		new[j] = (*args)[j];
		j++;
	}
	new[i] = op;
	new[i + 1] = rest;
	shift_after_insert(new, *args, i, n);
	free((*args)[i]);
	free(*args);
	*args = new;
	return (1);
}

void	split_one_redir(char ***args, int i)
{
	int		k;
	char	*op;
	char	*rest;

	k = 1 + (((*args)[i][0] == '>' || (*args)[i][0] == '<')
			&& (*args)[i][1] == (*args)[i][0]);
	op = dup_redir_op((*args)[i]);
	rest = ft_strdup((*args)[i] + k);
	if (op && rest && *rest)
		insert_split_token(args, i, op, rest);
	else
		free_split_parts(op, rest);
}

void	normalize_redirs(char ***args)
{
	int	i;

	i = 0;
	while (*args && (*args)[i])
	{
		if (is_redir_prefix((*args)[i]) && ft_strlen((*args)[i]) > 1)
			split_one_redir(args, i);
		i++;
	}
}

int	count_nonempty(char **a)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (a && a[i])
	{
		if (a[i][0] != '\0')
			n++;
		i++;
	}
	return (n);
}

void	compact_empty_args(char ***args)
{
	char	**a;
	char	**new;
	int		i;
	int		j;

	a = *args;
	new = ft_calloc(count_nonempty(a) + 1, sizeof(char *));
	if (!new)
		return ;
	i = 0;
	j = 0;
	while (a && a[i])
	{
		if (a[i][0] != '\0')
			new[j++] = a[i];
		else
			free(a[i]);
		i++;
	}
	free(a);
	*args = new;
}
