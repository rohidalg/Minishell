/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:36:17 by rohidalg          #+#    #+#             */
/*   Updated: 2026/01/26 19:56:10 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_getenv(char *name, char **env)
{
	int		i;
	int		len;
	char	*result;

	if (!env || !name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, len) && env[i][len] == '=')
		{
			result = env[i] + len + 1;
			return (result);
		}
		i++;
	}
	return (NULL);
}

char	*ft_getpath(char *cmd, char **env)
{
	char	**path;
	char	*res;
	char	*path_env;

	res = NULL;
	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			res = ft_strdup(cmd);
		if (access(cmd, X_OK) == 0)
    		res = ft_strdup(cmd);
		return (res);
	}
	path_env = ft_getenv("PATH", env);
	if (!path_env)
		return (NULL);
	path = ft_split(path_env, ':');
	if (!path)
		return (NULL);
	res = ft_check_path(path, cmd);
	ft_free(path);
	return (res);
}


void	ft_son(char **argv, char **env, int *fd_p)
{
	int	fd;

	fd = ft_file(argv[1], 0);
	dup2(fd, 0);
	dup2(fd_p[1], 1);
	close(fd_p[0]);
	ft_exec(argv[2], env);
}

void	ft_father(char **argv, char **env, int *fd_p)
{
	int	fd;

	fd = ft_file(argv[4], 1);
	dup2(fd, 1);
	dup2(fd_p[0], 0);
	close(fd_p[1]);
	ft_exec(argv[3], env);
}

// int	main(int argc, char **argv, char **env)
// {
// 	int		fd_p[2];
// 	pid_t	pid;
// 	int		status;

// 	ft_check_argv(argc, argv);
// 	if (pipe(fd_p) == -1)
// 		exit(-1);
// 	pid = fork();
// 	if (pid == -1)
// 		exit(-1);
// 	if (pid == 0)
// 		ft_son(argv, env, fd_p);
// 	waitpid(pid, &status, 0);
// 	ft_father(argv, env, fd_p);
// 	return (0);
// }
