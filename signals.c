/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 22:04:24 by wiljimen          #+#    #+#             */
/*   Updated: 2026/01/21 01:14:23 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_exit_status = 130;
//volatile -> evita optimizaciones incorrectas
//sig_atomic_t -> seguridad frente a señales

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: you <you@student.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20                               #+#    #+#             */
/*   Updated: 2026/01/20                               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>

// 130 es el codigo convencional de SIGINT.
volatile sig_atomic_t	g_exit_status = 0;

static void	sigint_interactive_handler(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	sigint_parent_wait_handler(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(STDOUT_FILENO, "\n", 1);
}

void	signals_set_interactive(void)
{
	struct sigaction	sa;

	// SIGINT (Ctrl-C)
	sa.sa_handler = sigint_interactive_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART; // helps readline recover
	sigaction(SIGINT, &sa, NULL);

	// SIGQUIT (Ctrl-\) ignored
	signal(SIGQUIT, SIG_IGN);
}

void	signals_set_child_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signals_set_parent_wait(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_parent_wait_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
