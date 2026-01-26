/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:46:56 by rohidalg          #+#    #+#             */
/*   Updated: 2026/01/25 23:11:24 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	redirect_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror(file);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	redirect_output(char *file, int append)
{
	int	fd;

	if (append)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(file);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static void	remove_two_tokens(char **args, int i)
{
	int	k;

	free(args[i]);
	free(args[i + 1]);
	k = i;
	while (args[k + 2])
	{
		args[k] = args[k + 2];
		k++;
	}
	args[k] = NULL;
	args[k + 1] = NULL;
}

static int	redirect_heredoc(char *delim)
{
	int		fd[2];
	char	*line;

	if (!delim || pipe(fd) == -1)
		return (perror("pipe"), -1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (close(fd[0]), close(fd[1]), -1);
		if (!strcmp(line, delim))
			break ;
		write(fd[1], line, strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		return (perror("dup2"), close(fd[0]), -1);
	return (close(fd[0]), 0);
}

char	**redirect(char **args)
{
	int	i;
	int	append;

	i = 0;
	while (args && args[i])
	{
		if (!ft_strcmp(args[i], "<<") && args[i + 1])
		{
			if (redirect_heredoc(args[i + 1]) < 0)
				return (NULL);
			remove_two_tokens(args, i);
			continue ;
		}
		if (!ft_strcmp(args[i], "<") && args[i + 1])
		{
			if (redirect_input(args[i + 1]) < 0)
				return (NULL);
			remove_two_tokens(args, i);
			continue ;
		}
		append = (!ft_strcmp(args[i], ">>"));
		if ((!ft_strcmp(args[i], ">") || append) && args[i + 1])
		{
			if (redirect_output(args[i + 1], append) < 0)
				return (NULL);
			remove_two_tokens(args, i);
			continue ;
		}
		i++;
	}
	return (args);
}

