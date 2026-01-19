/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:25:21 by rohidalg          #+#    #+#             */
/*   Updated: 2026/01/19 17:45:08 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*expand_in_quotes(const char *str, char **env)
{
	int		i;
	int		start;
	int		v;
	char	*var;

	i = 0;
	start = ++i;
	while (str[i] && str[i] != '"')
	{
		if (str[i] == '$')
		{
			v = ++i;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			var = ft_getenv(ft_substr(str, v, i - v), env);
			return (ft_strjoin(ft_substr(str, start, v - start - 1), var));
		}
		i++;
	}
	return (ft_substr(str, start, i - start));
}

char	*ft_quotes(const char *str, char **env)
{
	int	i;
	int	start;

	i = 0;
	if (str[i] == '\'')
	{
		start = ++i;
		while (str[i] && str[i] != '\'')
			i++;
		return (ft_substr(str, start, i - start));
	}
	if (str[i] == '"')
		return (expand_in_quotes(str, env));
	return (ft_strdup(str));
}
