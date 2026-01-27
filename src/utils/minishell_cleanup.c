/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cleanup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 01:12:00 by wiljimen          #+#    #+#             */
/*   Updated: 2026/01/27 19:09:40 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_str_array(char ***arr)
{
	int	i;

	if (!arr || !*arr)
		return ;
	i = 0;
	while ((*arr)[i])
		free((*arr)[i++]);
	free(*arr);
	*arr = NULL;
}

static void	free_vars_list(t_vars **vars)
{
	t_vars	*cur;
	t_vars	*next;

	if (!vars || !*vars)
		return ;
	cur = *vars;
	while (cur)
	{
		next = cur->next;
		free(cur->name);
		free(cur->value);
		free(cur);
		cur = next;
	}
	*vars = NULL;
}

void	minishell_cleanup(char ***env, t_vars **vars)
{
	free_str_array(env);
	free_vars_list(vars);
	rl_clear_history();
}
