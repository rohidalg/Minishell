/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:46:56 by rohidalg          #+#    #+#             */
/*   Updated: 2026/01/19 15:37:43 by rohidalg         ###   ########.fr       */
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

char	**redirect(char **args)
{
	int	i;
	int	append;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '<' && !args[i][1] && args[i + 1])
		{
			if (redirect_input(args[i + 1]) < 0)
				return (NULL);
			remove_two_tokens(args, i);
			continue ;
		}
		if (args[i][0] == '>' && args[i + 1])
		{
			append = (args[i][1] == '>');
			if (redirect_output(args[i + 1], append) < 0)
				return (NULL);
			remove_two_tokens(args, i);
			continue ;
		}
		i++;
	}
	return (args);
}
