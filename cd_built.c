/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:00:10 by wiljimen          #+#    #+#             */
/*   Updated: 2026/01/27 18:32:33 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_is_dash(char **args)
{
	if (args[1] && args[1][0] == '-' && args[1][1] == '\0')
		return (1);
	return (0);
}

void	cd_chdir_fail(char *target)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(target, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
}

char	**cd_update_pwds(t_vars **vars, char **g_env, char *oldpwd,
		char *newpwd)
{
	char	*line;

	if (oldpwd)
	{
		line = ft_strjoin("OLDPWD=", oldpwd);
		if (line)
		{
			if (!vars_set_if_exists(line, *vars))
				vars_add_new(line, vars);
			g_env = env_set(line, g_env);
			free(line);
		}
	}
	if (newpwd)
	{
		line = ft_strjoin("PWD=", newpwd);
		if (line)
		{
			if (!vars_set_if_exists(line, *vars))
				vars_add_new(line, vars);
			g_env = env_set(line, g_env);
			free(line);
		}
	}
	return (g_env);
}

static void	cd_cleanup(char *oldpwd, char *target, char *newpwd, int status)
{
	free(oldpwd);
	free(target);
	free(newpwd);
	g_exit_status = status;
}

char	**builtin_cd(char **args, t_vars **vars, char **g_env)
{
	char	*target;
	char	*oldpwd;
	char	*newpwd;

	oldpwd = getcwd(NULL, 0);
	target = cd_choices(args, *vars);
	if (!target)
	{
		cd_cleanup(oldpwd, NULL, NULL, 1);
		return (g_env);
	}
	if (chdir(target) == -1)
	{
		cd_chdir_fail(target);
		cd_cleanup(oldpwd, target, NULL, 1);
		return (g_env);
	}
	newpwd = getcwd(NULL, 0);
	g_env = cd_update_pwds(vars, g_env, oldpwd, newpwd);
	if (cd_is_dash(args) && newpwd)
		printf("%s\n", newpwd);
	cd_cleanup(oldpwd, target, newpwd, 0);
	return (g_env);
}
