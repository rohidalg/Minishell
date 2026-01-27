/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 19:44:00 by rohidalg          #+#    #+#             */
/*   Updated: 2026/01/27 19:09:12 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_q(char c, char *q)
{
	if (*q == 0 && (c == '\'' || c == '"'))
		*q = c;
	else if (*q == c)
		*q = 0;
}

static int	print_pipe_syntax(void)
{
	ft_putendl_fd("syntax error near unexpected token `|'", 2);
	return (1);
}

static int	handle_pipe_char(char c, char q, int *seen_word, int *last_pipe)
{
	if (q == 0 && c == '|')
	{
		if (!*seen_word || *last_pipe)
			return (print_pipe_syntax());
		*last_pipe = 1;
		*seen_word = 0;
	}
	else if (q == 0 && c != '|' && c != ' ' && c != '\t')
	{
		*last_pipe = 0;
		*seen_word = 1;
	}
	return (0);
}

int	pipe_syntax_str(char *s)
{
	int		i;
	int		last_pipe;
	int		seen_word;
	char	q;

	i = 0;
	last_pipe = 0;
	seen_word = 0;
	q = 0;
	while (s && s[i])
	{
		update_q(s[i], &q);
		if (handle_pipe_char(s[i], q, &seen_word, &last_pipe))
			return (print_pipe_syntax());
		i++;
	}
	if (last_pipe)
		return (print_pipe_syntax());
	return (0);
}
