/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:46:56 by rohidalg          #+#    #+#             */
/*   Updated: 2026/01/08 19:39:49 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int redirect_input(char *file)
{
    int fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        perror(file);
        return -1;
    }
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

void redirect_output(char *file, int append)
{
    int fd;

    if (append)
        fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1)
    {
        perror(file);
        return;
    }

    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        close(fd);
        return;
    }

    close(fd);
}

char **redirect(char **args)
{
    int i;
    int j;
    int append;

    i = 0;
    while (args[i])
    {
        if (args[i][0] == '<' && !args[i][1] && args[i + 1])
            redirect_input(args[i + 1]);
        else if (args[i][0] == '>' && args[i + 1])
        {
            append = (args[i][1] == '>');
            redirect_output(args[i + 1], append);
        }
        else
        {
            i++;
            continue;
        }
        free(args[i]);
        free(args[i + 1]);

        j = i;
        while (args[j + 2])
        {
            args[j] = args[j + 2];
            j++;
        }
        args[j] = NULL;
    }
    return (args);
}
