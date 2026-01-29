/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:48:45 by wiljimen          #+#    #+#             */
/*   Updated: 2026/01/29 16:57:03 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	prepare_mini_args(char ***args)
{
	char	*tmp;

	if (!args || !*args)
		return ;
	tmp = **args;
	**args = remove_quotes(tmp);
	free(tmp);
	normalize_redirs(args);
	compact_empty_args(args);
}

int	main(int argc, char **argv, char **env)
{
	char	**g_env;
	t_vars	*vars;

	(void)argc;
	(void)argv;
	g_env = NULL;
	g_env = get_entire_env(env);
	vars = init_vars_from_env(g_env);
	header(&g_env, &vars);
	minishell_cleanup(&g_env, &vars);
	rl_clear_history();
	clear_history();
	return (g_exit_status);
}
