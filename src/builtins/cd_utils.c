/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:39:56 by wiljimen          #+#    #+#             */
/*   Updated: 2026/01/27 19:06:49 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*vars_get_value(t_vars *vars, char *name)
{
	t_vars	*node;

	if (!vars || !name)
		return (NULL);
	node = vars_find(vars, name);
	if (!node)
		return (NULL);
	return (node->value);
}

void	cd_error(char *var)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(var, 2);
	ft_putendl_fd(" not set", 2);
}

char	*cd_choices(char **args, t_vars *vars)
{
	char	*value;

	if (!args[1])
	{
		value = vars_get_value(vars, "HOME");
		if (!value || !*value)
			return (cd_error("HOME"), NULL);
		return (ft_strdup(value));
	}
	if (args[1][0] == '-' && args[1][1] == '\0')
	{
		value = vars_get_value(vars, "OLDPWD");
		if (!value || !*value)
			return (cd_error("OLDPWD"), NULL);
		return (ft_strdup(value));
	}
	return (ft_strdup(args[1]));
}

char	*join_var(char *var, char *value)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, value);
	free(tmp);
	return (res);
}

void	set_var_both(char *line, t_vars **vars, char ***g_env)
{
	if (!line)
		return ;
	if (!vars_set_if_exists(line, *vars))
		vars_add_new(line, vars);
	*g_env = env_set(line, *g_env);
}
