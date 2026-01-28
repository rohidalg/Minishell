/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:31:39 by will              #+#    #+#             */
/*   Updated: 2026/01/28 15:07:50 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			g_exit_status = 0;

int	check_built_in(char **cmd, char ***g_env, t_vars **vars)
{
	if (!cmd || !cmd[0])
		return (0);
	if (!ft_strcmp(cmd[0], "pwd") || !ft_strcmp(cmd[0], "exit")
		|| !ft_strcmp(cmd[0], "env"))
	{
		pwd_exit_env(cmd, g_env);
		return (1);
	}
	if (!ft_strcmp(cmd[0], "unset") || !ft_strcmp(cmd[0], "export")
		|| !ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "echo"))
	{
		unset_export_cd_echo(cmd, g_env, vars);
		return (1);
	}
	return (0);
}

static void	run_parsed(char **args, char ***g_env, t_vars **vars)
{
	int	is_builtin;

	is_builtin = check_built_in(args, g_env, vars);
	if (!is_builtin)
		run_exec_args(args, *g_env);
}

void	pipex_or_builtin(char *input, char ***g_env, t_vars **vars)
{
	char	**args;

	args = ft_split(input, ' ');
	if (!args || !args[0])
	{
		ft_free(args);
		return ;
	}
	expand_args_skip(args, *g_env, g_exit_status);
	apply_quotes(args, *g_env);
	run_parsed(args, g_env, vars);
	ft_free(args);
}

int	header(char ***g_env, t_vars **vars)
{
	char	*input;

	while (1)
	{
		handle_signals();
		input = readline("minishell> ");
		if (!input)
		{
			if (isatty(STDIN_FILENO))
				ft_putendl_fd("", 2);
			break ;
		}
		if (*input && !invalid_input(input))
		{
			add_history(input);
			pipex_or_builtin(input, g_env, vars);
		}
		free(input);
	}
	return (0);
}

void	run_pipex(char *input, char **g_env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		ft_exec(input, g_env);
		exit(127);
	}
	else
		waitpid(pid, &status, 0);
}
