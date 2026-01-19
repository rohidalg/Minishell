/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:31:39 by will              #+#    #+#             */
/*   Updated: 2026/01/19 17:29:08 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

void	check_built_in(char **cmd, char ***g_env, t_vars **vars)
{
	if (!cmd || cmd[0] == NULL)
		return ;
	if (ft_strcmp(cmd[0], "pwd") == 0
		|| ft_strcmp(cmd[0], "exit")  == 0
		|| ft_strcmp(cmd[0], "env") == 0)
		pwd_exit_env(cmd, g_env);
	else if (ft_strcmp(cmd[0], "unset") == 0
		|| ft_strcmp(cmd[0], "export") == 0
		|| ft_strcmp(cmd[0], "cd") == 0)
		unset_export_cd_echo(cmd, g_env, vars);
}

int	header(char **g_env, t_vars **vars)
{
	char	*input;
	char	**cmd;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		if (*input)
		{
			if (!invalid_input(input))
			{
				cmd = ft_split(input, ' ');
				if (cmd && cmd[0])
					check_built_in(cmd, env, g_env, vars);
				add_history(input);
				run_pipex(input, env);
				ft_free(cmd);
			}
		}
		free(input);
	}
	return (0);
}

void	run_pipex(char *input, char **g_env)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		ft_exec(input, g_env); // Proceso hijo: ejecuta el comando
		exit(127);
	}
	else
		waitpid(pid, &status, 0); // Proceso padre: espera a que termine el hijo
}

int main(int argc, char **argv, char **env)
{
	char	**g_env;
	t_vars	*vars;

	(void)argc;
	(void)argv;
	g_env = NULL;
	g_env = get_entire_env(env);
	vars = init_vars_from_env(g_env);
	header(g_env, &vars);
	return (0);
}

// implementar el pipe y que acepte los '\' entre comillas