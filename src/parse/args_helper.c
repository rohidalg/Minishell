/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:09:07 by wiljimen          #+#    #+#             */
/*   Updated: 2026/01/29 17:04:54 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redir_prefix(const char *s)
{
	return (s && (s[0] == '<' || s[0] == '>'));
}

char	*dup_redir_op(const char *s)
{
	if (s[0] == '>' && s[1] == '>')
		return (ft_strdup(">>"));
	if (s[0] == '<' && s[1] == '<')
		return (ft_strdup("<<"));
	return (ft_substr(s, 0, 1));
}

int	count_args(char **a)
{
	int	n;

	n = 0;
	while (a && a[n])
		n++;
	return (n);
}

void	shift_after_insert(char **new, char **old, int i, int n)
{
	int	j;

	j = i + 1;
	while (j < n)
	{
		new[j + 1] = old[j];
		j++;
	}
}
