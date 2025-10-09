/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:24:05 by rohidalg          #+#    #+#             */
/*   Updated: 2025/10/09 19:23:00 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "pipex/pipex.h"
# include "pipex/pipex.h"
# include <pthread.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>

// volatile sig_atomic_t g_signal = 0;

extern char	**g_env;


//------------------------parse.c------------------------//
void	ft_global(void);
void	run_pipex(char *input, char **env);
int		header(char **env, char **g_env);
void	run_pipex(char *input, char **env);

//------------------------BUILTS-IN------------------------//

void	built_pwd(void);
void	check_built_in(char *cmd, char **g_env);
void	built_cd(char **cmd);
void	built_env(char **g_env);
char	**get_entire_env(char **env);

//------------------------MINI_UTILS.C------------------------//
char	*expand_dolar(const char *str);


#endif