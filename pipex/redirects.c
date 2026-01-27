/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:46:56 by rohidalg          #+#    #+#             */
/*   Updated: 2026/01/27 16:52:30 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

static int	handle_redirect_token(char **args, int i)
{
	int	append;

	if (!ft_strcmp(args[i], "<<") && args[i + 1])
	{
		if (redirect_heredoc(args[i + 1]) < 0)
			return (-1);
		remove_two_tokens(args, i);
		return (1);
	}
	if (!ft_strcmp(args[i], "<") && args[i + 1])
	{
		if (redirect_input(args[i + 1]) < 0)
			return (-1);
		remove_two_tokens(args, i);
		return (1);
	}
	append = (!ft_strcmp(args[i], ">>"));
	if ((!ft_strcmp(args[i], ">") || append) && args[i + 1])
	{
		if (redirect_output(args[i + 1], append) < 0)
			return (-1);
		remove_two_tokens(args, i);
		return (1);
	}
	return (0);
}

char	**redirect(char **args)
{
	int	i;
	int	r;

	i = 0;
	while (args && args[i])
	{
		r = handle_redirect_token(args, i);
		if (r < 0)
			return (NULL);
		if (r == 1)
			continue ;
		i++;
	}
	return (args);
}
