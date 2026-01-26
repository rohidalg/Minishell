/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 19:34:03 by wiljimen          #+#    #+#             */
/*   Updated: 2026/01/26 19:49:31 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	expand_args_skip_heredoc(char **args, char **env, int last)
// {
// 	int		i;
// 	char	*tmp;

// 	i = 0;
// 	while (args && args[i])
// 	{
// 		if (!ft_strcmp(args[i], "<<") && args[i + 1])
// 		{
// 			i += 2;
// 			continue ;
// 		}
// 		tmp = expand_string(args[i], env, last);
// 		free(args[i]);
// 		args[i] = tmp;
// 		i++;
// 	}
// }

// void	run_exec_args(char **args, char **g_env)
// {
// 	pid_t	pid;
// 	int		st;

// 	pid = fork();
// 	if (pid < 0)
// 		return ((void)perror("fork"));
// 	if (pid == 0)
// 	{
// 		if (!redirect(args))
// 			exit(1);
// 		ft_exec_args(args, g_env);
// 		exit(127);
// 	}
// 	if (waitpid(pid, &st, 0) > 0)
// 		g_exit_status = exit_from_wait_status(st);
// }

// int	exec_error(char *cmd)
// {
// 	if (errno == ENOENT)
// 		return (ft_putstr_fd("minishell: ", 2),
// 			ft_putstr_fd(cmd, 2),
// 			ft_putendl_fd(": command not found", 2), 127);
// 	return (ft_putstr_fd("minishell: ", 2),
// 		ft_putstr_fd(cmd, 2),
// 		ft_putendl_fd(": permission denied", 2), 126);
// }
