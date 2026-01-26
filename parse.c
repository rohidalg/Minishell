/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:31:39 by will              #+#    #+#             */
/*   Updated: 2026/01/26 20:06:44 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_exit_status = 0;

int	check_built_in(char **cmd, char ***g_env, t_vars **vars)
{
	if (!cmd || cmd[0] == NULL)
		return (0);
	if (ft_strcmp(cmd[0], "pwd") == 0 || ft_strcmp(cmd[0], "exit") == 0
		|| ft_strcmp(cmd[0], "env") == 0)
	{
		pwd_exit_env(cmd, g_env);
		return (1);
	}
	else if (ft_strcmp(cmd[0], "unset") == 0 || ft_strcmp(cmd[0], "export") == 0
		|| ft_strcmp(cmd[0], "cd") == 0 || ft_strcmp(cmd[0], "echo") == 0)
	{
		unset_export_cd_echo(cmd, g_env, vars);
		return (1);
	}
	return (0);
}

void	pipex_or_builtin(char *input, char ***g_env, t_vars **vars)
{
	char	**args;
	int		is_builtin;

	if (has_pipe(input))
		return (run_pipeline(input, *g_env));
	args = split_quote_aware(input);
	if (!args || !args[0])
	{
		ft_free(args);	
		return ;
	}
	expand_args_skip_heredoc(args, *g_env, g_exit_status);
	is_builtin = check_built_in(args, g_env, vars);
	if (!is_builtin)
		run_exec_args(args, *g_env);
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
			ft_putstr_fd("exit\n", 2);
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
		ft_exec(input, g_env); // Proceso hijo: ejecuta el comando
		exit(127);
	}
	else
		waitpid(pid, &status, 0); // Proceso padre: espera a que termine el hijo
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
	return (g_exit_status);
}
