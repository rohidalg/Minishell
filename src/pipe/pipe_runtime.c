/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_runtime.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 19:45:43 by rohidalg          #+#    #+#             */
/*   Updated: 2026/01/27 19:09:07 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	safe_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) < 0)
	{
		perror("dup2");
		exit(1);
	}
}

void	child_stage(t_stage st)
{
	if (st.prev != -1)
		safe_dup2(st.prev, STDIN_FILENO);
	if (!st.last)
		safe_dup2(st.fd[1], STDOUT_FILENO);
	if (st.prev != -1)
		close(st.prev);
	if (!st.last)
	{
		close(st.fd[0]);
		close(st.fd[1]);
	}
	ft_exec(st.cmd, st.env);
	exit(127);
}

void	wait_pids(pid_t *p, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (p[i] > 0)
			waitpid(p[i], NULL, 0);
		i++;
	}
}

void	cleanup_pipeline(t_pipe_data *d, int started)
{
	if (d->prev != -1)
		close(d->prev);
	wait_pids(d->pids, started);
	ft_free(d->cmds);
	free(d->pids);
}
