/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts_in_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:09:38 by will23            #+#    #+#             */
/*   Updated: 2025/12/20 17:21:58 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_cd(char **cmd)
{
	if (cmd[1] == NULL)
		chdir(getenv("HOME"));
	else if (cmd[1] != 0)
		perror("cd");
}

void	built_pwd(void)
{
	char	*cwd;

	cwd = malloc(1024);
	if (!cwd)
	{
		free(cwd);
		exit(EXIT_FAILURE);
	}
	if (getcwd(cwd, 1024) != NULL)
		printf("%sAA\n", cwd);
	else
		perror("pwd");
	free(cwd);
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
