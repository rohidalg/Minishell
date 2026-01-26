/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 22:42:58 by rohidalg          #+#    #+#             */
/*   Updated: 2026/01/25 20:21:58 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int has_pipe(char *s)
{
    int i;

    i = 0;
    while (s && s[i])
    {
        if (s[i] == '|')
            return (1);
        i++;
    }
    return (0);
}
static void trim_cmd(char *s)
{
    int i;
    int end;

    if (!s)
        return;
    i = 0;
    while (s[i] == ' ' || s[i] == '\t')
        i++;
    if (i)
        ft_memmove(s, s + i, ft_strlen(s + i) + 1);
    end = (int)ft_strlen(s);
    while (end > 0 && (s[end - 1] == ' ' || s[end - 1] == '\t' || s[end - 1] == '\n' || s[end - 1] == '\r'))
        s[--end] = '\0';
}

static int array_len(char **a)
{
    int i;

    i = 0;
    while (a && a[i])
        i++;
    return (i);
}

static void wait_pids(pid_t *p, int n)
{
    int i;

    i = 0;
    while (i < n)
    {
        if (p[i] > 0)
            waitpid(p[i], NULL, 0);
        i++;
    }
}

static void close_fds(int prev, int *fd, int has_fd)
{
    if (prev != -1)
        close(prev);
    if (has_fd)
    {
        close(fd[0]);
        close(fd[1]);
    }
}

static void child_stage(int prev, int *fd, int last, char *cmd, char **env)
{
    if (prev != -1 && dup2(prev, 0) < 0)
        exit(1);
    if (!last && dup2(fd[1], 1) < 0)
        exit(1);
    close_fds(prev, fd, !last);
    ft_exec(cmd, env);
    exit(127);
}

static void pipeline_fail(char **cmds, pid_t *p, int i, int *fd)
{
    if (i > 0)
        close_fds(-1, fd, 1);
    wait_pids(p, i);
    ft_free(cmds);
    free(p);
}

void run_pipeline(char *input, char **env)
{
    char **cmds;
    pid_t *p;
    int i, n, prev, fd[2];

    cmds = ft_split(input, '|');
    n = array_len(cmds);
    p = malloc(sizeof(pid_t) * n); // error de malloc, hay que arreglarlo
    if (!cmds || n == 0 || !p)
        return (ft_free(cmds), free(p));
    i = -1;
    while (++i < n)
        trim_cmd(cmds[i]);
    prev = -1;
    i = 0;
    while (i < n)
    {
        if (i < n - 1 && pipe(fd) == -1)
            return (perror("pipe"), pipeline_fail(cmds, p, i, fd));
        p[i] = fork();
        if (p[i] == 0)
            child_stage(prev, fd, (i == n - 1), cmds[i], env);
        if (p[i] < 0)
            return (perror("fork"), pipeline_fail(cmds, p, i, fd));
        if (prev != -1)
            close(prev);
        if (i < n - 1)
            close(fd[1]), prev = fd[0];
        i++;
    }
    wait_pids(p, n);
    ft_free(cmds);
    free(p);
}

void run_line(char *input, char **env)
{
    if (!input || !*input)
        return;
    if (has_pipe(input))
        run_pipeline(input, env);
    else
        run_pipex(input, env);
}
