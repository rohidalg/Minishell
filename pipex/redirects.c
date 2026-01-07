/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:46:56 by rohidalg          #+#    #+#             */
/*   Updated: 2026/01/07 20:08:45 by rohidalg         ###   ########.fr       */
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

void redirect(char **cmmd_part)
{
    int i = 0;
    while (cmmd_part[i])
    {
        if (strcmp(cmmd_part[i], "<") == 0 && cmmd_part[i + 1])
        {
            redirect_input(cmmd_part[i + 1]);
            cmmd_part[i] = cmmd_part[i + 1] = NULL;
        }
        else if (strcmp(cmmd_part[i], ">") == 0 && cmmd_part[i + 1])
        {
            redirect_output(cmmd_part[i + 1], 0);
            cmmd_part[i] = cmmd_part[i + 1] = NULL;
        }
        else if (strcmp(cmmd_part[i], ">>") == 0 && cmmd_part[i + 1])
        {
            redirect_output(cmmd_part[i + 1], 1);
            cmmd_part[i] = cmmd_part[i + 1] = NULL;
        }
        i++;
    }
}

// me falta poner free para que no se colapse cuando hago este ejemplo
// (./minishell
// minishell> echo "línea 1" >> test2.txt
// minishell> echo "línea 2" >> test2.txt
// minishell> cat test2.txt
// línea 1
// línea 2
// minishell> cat < test2.txt
// línea 1
// línea 2
// minishell> grep "línea 1" < test2.txt
// línea 1
// test2.txt
// línea: No such file or directory
// ^C)