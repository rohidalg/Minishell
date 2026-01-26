/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_trim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 19:45:00 by rohidalg          #+#    #+#             */
/*   Updated: 2026/01/26 19:45:19 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	trim_cmd(char *s)
{
	int	i;
	int	end;

	if (!s)
		return ;
	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (i)
		ft_memmove(s, s + i, ft_strlen(s + i) + 1);
	end = (int)ft_strlen(s);
	while (end > 0 && (s[end - 1] == ' ' || s[end - 1] == '\t'
			|| s[end - 1] == '\n' || s[end - 1] == '\r'))
		s[--end] = '\0';
}

void	trim_all(char **cmds)
{
	int	i;

	i = 0;
	while (cmds && cmds[i])
	{
		trim_cmd(cmds[i]);
		i++;
	}
}

int	array_len(char **a)
{
	int	i;

	i = 0;
	while (a && a[i])
		i++;
	return (i);
}
