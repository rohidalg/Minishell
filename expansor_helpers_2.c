/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_helpers_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:33:16 by wiljimen          #+#    #+#             */
/*   Updated: 2026/01/27 17:37:25 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_args(char **args, char **env)
{
	char	*path;

	if (!args || !args[0] || !args[0][0])
		exit(0);

	path = ft_getpath(args[0], env);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	execve(path, args, env);
	free(path);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putendl_fd(": permission denied", 2);
	exit(126);
}

void	expand_args_skip(char **args, char **env, int last)
{
	int		i;
	char	*tmp;
	i = 0;
	while (args && args[i])
	{
		if (!ft_strcmp(args[i], "<<") && args[i + 1])
		{
			i += 2;
			continue ;
		}
		tmp = expand_string(args[i], env, last);
		free(args[i]);
		args[i] = tmp;
		i++;
	}
}

static int	exit_from_wait(int st)
{
	if (WIFEXITED(st))
		return (WEXITSTATUS(st));
	if (WIFSIGNALED(st))
		return (128 + WTERMSIG(st));
	return (1);
}

void	run_exec_args(char **args, char **g_env)
{
	pid_t	pid;
	int		st;

	pid = fork();
	if (pid < 0)
		return ((void)perror("fork"));
	if (pid == 0)
	{
		if (!redirect(args))
			exit(1);
		ft_exec_args(args, g_env);
		exit(127);
	}
	if (waitpid(pid, &st, 0) > 0)
		g_exit_status = exit_from_wait(st);
}
