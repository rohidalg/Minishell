/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: will23 <will23@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:31:39 by will              #+#    #+#             */
/*   Updated: 2025/12/06 15:32:02 by will23           ###   ########.fr       */
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
	char	*input; // puntero para guardar lo que se escribe
	char	**cmd;
	int		i;

	i = 0;
	while (1)
	{
		input = readline("minishell> "); // muestra "minishell> " y espera input
		if (!input)
			break ; // si el usuario pulsa Ctrl+D (EOF),salimos
		else if (*input) // si la línea no está vacía (no es solo Enter)
		{
			add_history(input); // guarda el comando en el historial
			cmd = ft_split(input, ' ');
			if(cmd && cmd[0])
				check_built_in(input, env, g_env, vars);
			run_pipex(input, env);
			while (cmd && cmd[i])
			{
				free(cmd[i]);
				i++;
			}
			free(cmd);
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
	(void)argc;
	(void)argv;
	char 	**g_env;
	t_vars	*vars;

	g_env = NULL;
	g_env = get_entire_env(env);
	vars = init_vars_from_env(g_env);
	header(env, g_env, &vars);
	return (0);
}

