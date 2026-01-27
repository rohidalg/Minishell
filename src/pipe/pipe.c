/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 22:42:58 by rohidalg          #+#    #+#             */
/*   Updated: 2026/01/27 19:09:22 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipeline_prepare(t_pipe_data *d, char *input)
{
	if (pipe_syntax_str(input))
		return (1);
	d->cmds = ft_split(input, '|');
	if (!d->cmds)
		return (1);
	trim_all(d->cmds);
	d->n = array_len(d->cmds);
	d->pids = malloc(sizeof(pid_t) * d->n);
	if (!d->pids)
	{
		ft_free(d->cmds);
		return (1);
	}
	d->prev = -1;
	d->i = 0;
	return (0);
}

static void	fill_stage(t_stage *st, t_pipe_data *d, char **env)
{
	st->prev = d->prev;
	st->fd[0] = d->fd[0];
	st->fd[1] = d->fd[1];
	st->last = (d->i == d->n - 1);
	st->cmd = d->cmds[d->i];
	st->env = env;
}

static int	open_pipe_if_needed(t_pipe_data *d)
{
	if (d->i < d->n - 1 && pipe(d->fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	return (0);
}

static int	fork_and_run(t_pipe_data *d, char **env)
{
	t_stage	st;

	d->pids[d->i] = fork();
	if (d->pids[d->i] == 0)
	{
		fill_stage(&st, d, env);
		child_stage(st);
	}
	if (d->pids[d->i] < 0)
	{
		perror("fork");
		return (1);
	}
	return (0);
}

void	run_pipeline(char *input, char **env)
{
	t_pipe_data	d;

	if (pipeline_prepare(&d, input))
		return ;
	while (d.i < d.n)
	{
		if (open_pipe_if_needed(&d))
			return (cleanup_pipeline(&d, d.i));
		if (fork_and_run(&d, env))
			return (cleanup_pipeline(&d, d.i));
		if (d.prev != -1)
			close(d.prev);
		if (d.i < d.n - 1)
		{
			close(d.fd[1]);
			d.prev = d.fd[0];
		}
		d.i++;
	}
	wait_pids(d.pids, d.n);
	ft_free(d.cmds);
	free(d.pids);
}
