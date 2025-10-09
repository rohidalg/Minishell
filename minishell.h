/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:24:05 by rohidalg          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/10/09 19:23:00 by rohidalg         ###   ########.fr       */
=======
/*   Updated: 2025/10/09 19:39:01 by wiljimen         ###   ########.fr       */
>>>>>>> upstream/master
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

extern char	**g_env;

typedef struct	s_vars{
	char	*name;
	char	*value;
	struct s_var *next;
}	t_vars;

//Name es el nombre de la variable, y Value el valor (Rodrigo=Bello)

//------------------------parse.c------------------------//
<<<<<<< HEAD
void	ft_global(void);
void	run_pipex(char *input, char **env);
=======

char	*ft_quote(char *input);
>>>>>>> upstream/master
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