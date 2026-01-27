/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others_built.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:09:38 by will23            #+#    #+#             */
/*   Updated: 2026/01/27 19:52:59 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("minishell: pwd");
		g_exit_status = 1;
		return ;
	}
	printf("%s\n", cwd);
	free(cwd);
	g_exit_status = 0;
}

char	**get_entire_env(char **env)
{
	int		i;
	int		j;
	char	**new_env;

	if (!env || !env[0])
		exit(EXIT_FAILURE);
	i = 0;
	while (env[i])
		i++;
	new_env = ft_calloc(i + 1, sizeof(char *));
	if (!new_env)
		exit(EXIT_FAILURE);
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
			j++;
		new_env[i] = ft_substr(env[i], 0, j);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	built_env(char **g_env)
{
	int	i;

	i = 0;
	while (g_env[i])
	{
		printf("%s\n", g_env[i]);
		i++;
	}
}

void	pwd_exit_env(char **cmd, char ***g_env)
{
	if (!cmd || cmd[0] == NULL)
		return ;
	if (ft_strcmp(cmd[0], "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(cmd[0], "exit") == 0)
		exit(EXIT_SUCCESS);
	else if (ft_strcmp(cmd[0], "env") == 0)
		built_env(*g_env);
}

void	unset_export_cd_echo(char **cmd, char ***g_env, t_vars **vars)
{
	if (!cmd || cmd[0] == NULL)
		return ;
	else if (ft_strcmp(cmd[0], "unset") == 0)
		*vars = builtin_unset(cmd, *vars, *g_env);
	else if (ft_strcmp(cmd[0], "export") == 0)
		*g_env = builtin_export(cmd, vars, *g_env);
	else if (strcmp(cmd[0], "cd") == 0)
		*g_env = builtin_cd(cmd, vars, *g_env);
	else if (strcmp(cmd[0], "echo") == 0)
		builtin_echo(cmd);
}
