/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_entry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 19:42:41 by rohidalg          #+#    #+#             */
/*   Updated: 2026/01/27 19:09:03 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_pipe(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

void	run_line(char *input, char **env)
{
	if (!input || !*input)
		return ;
	if (has_pipe(input))
		run_pipeline(input, env);
	else
		run_pipex(input, env);
}
