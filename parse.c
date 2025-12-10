/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:31:39 by will              #+#    #+#             */
/*   Updated: 2025/12/10 16:57:08 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_built_in(char **cmd, char **env, char **g_env, t_vars **vars)
{
	if (!cmd || cmd[0] == NULL)
		return ;
	if (strcmp(cmd[0], "pwd") == 0)
		built_pwd();
	else if (strcmp(cmd[0], "exit") == 0)
	exit(EXIT_SUCCESS);
	else if (strcmp(cmd[0], "env") == 0)
	built_env(g_env);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		*vars = builtin_unset(cmd, *vars, env, g_env);
	// else if (strcmp(cmd, "cd") == 0)
	// 	built_cd(cmd[1]);
}

int	header(char **env, char **g_env, t_vars **vars)
{
	char	*input;
	char	**cmd;
	int		i;

	while (1)
	{
		i = 0;
		input = readline("minishell> ");
		if (!input) // CTRL+D
			break ;
		if (*input) // Si no está vacío
		{
			if (!invalid_input(input))
			// Solo continúa si no hay caracteres prohibidos
			{
				add_history(input);
				cmd = ft_split(input, ' ');
				if (cmd && cmd[0])
					check_built_in(input, env, g_env, vars);
				run_pipex(input, env);
				while (cmd && cmd[i])
				{
					free(cmd[i]);
					i++;
				}
				free(cmd);
			}
		}
		free(input);
	}
	return (0);
}

void	run_pipex(char *input, char **env)
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
		// Proceso hijo: ejecuta el comando
		ft_exec(input, env);
		exit(127);
	}
	else
	{
		// Proceso padre: espera a que termine el hijo para volver a la minishell
		waitpid(pid, &status, 0);
	}
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
	header(env, g_env, &vars);
	return (0);
}
