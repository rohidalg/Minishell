/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:31:39 by will              #+#    #+#             */
/*   Updated: 2025/12/20 17:19:01 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_built_in(char **cmd, char ***g_env, t_vars **vars)
{
	if (!cmd || cmd[0] == NULL)
		return ;
	if (strcmp(cmd[0], "pwd") == 0)
		built_pwd();
	else if (strcmp(cmd[0], "exit") == 0)
		exit(EXIT_SUCCESS);
	else if (strcmp(cmd[0], "env") == 0)
		built_env(*g_env);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		*vars = builtin_unset(cmd, *vars, *g_env);
	else if (ft_strcmp(cmd[0], "export") == 0)
    	*g_env = builtin_export(cmd, vars, *g_env);
}
// else if (strcmp(cmd, "cd") == 0)
// 	built_cd(cmd[1]);

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
					check_built_in(cmd, &g_env, vars);
				add_history(input);
				run_pipex(input, g_env);
				ft_free(cmd);
			}
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
	header(g_env, &vars);
	return (0);
}
