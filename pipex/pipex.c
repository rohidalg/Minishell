/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:36:17 by rohidalg          #+#    #+#             */
/*   Updated: 2025/03/26 00:30:04 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_son(char **argv, int argc, char **env, int *fd_p)
{
	int fd;

	fd = ft_file(argv[1], 0);
	dup2(fd, 0);	  // redirige stdin al archivo
	dup2(fd_p[1], 1); // redirige stdout al pipe de escritura
	close(fd_p[0]);
	ft_exec(argv[2], env);
}

void ft_father(char **argv, char **env, int *fd_p)
{
	int fd;

	fd = ft_file(argv[4], 1);

	dup2(fd, 1);	  // redirige stdout al archivo
	dup2(fd_p[0], 0); // redirige stdin a la lectura del pipe
	close(fd_p[1]);
	ft_exec(argv[3], env);
}

// La idea es separar los comandos con otras condiciones, por ejemplo, los comandos siempre serán
// argc - 3, por que el 1 es el ./pipex, el 2 es el infile y el argc es el outfile,
// solo que no me acuerdo bien de como era hacer los hijos xD, pero voy poco a poco.

void	fork_necessary(char **argv, char **env, int argc)
{
	int		i;
	int		prev_fd;
	int		cmd_count;
	int		pipe_fd[2];

	i = 0;
	cmd_count = argc - 3;
	prev_fd = ft_file(argv[1], 0);
	while (i < cmd_count)
	{

	}

}

void	ft_fork_son(char **argv, char **env, int i, int inf_fd, int *pipe_fd)
{
	pid_t	pid;
	int		out_fd;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{

	}
}

int main(int argc, char **argv, char **env)
{
	int fd_p[2];
	pid_t pid;
	int status;

	ft_check_argv(argc, argv);
	if (pipe(fd_p) == -1)
		exit(-1);
	fork_necessary(argc - 3)
	/*pid = fork();
	if (pid == -1)
		exit(-1);
	if (pid == 0)
		ft_son(argv, env, fd_p);*/
	waitpid(pid, &status, 0);
	ft_father(argv, env, fd_p);
	return (0);
}
