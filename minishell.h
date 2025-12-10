/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:24:05 by rohidalg          #+#    #+#             */
/*   Updated: 2025/12/10 16:51:27 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "pipex/pipex.h"
# include <pthread.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

extern char			**g_env;

typedef struct s_vars
{
	char			*name;
	char			*value;
	struct s_var	*next;
}					t_vars;

// Name es el nombre de la variable, y Value el valor (Rodrigo=Bello)

//------------------------parse.c------------------------//

int					header(char **env, char **g_env, t_vars **vars);
void				run_pipex(char *input, char **env);

//------------------------BUILTS-IN------------------------//

void				built_pwd(void);
void				check_built_in(char **cmd, char **env, char **g_env, t_vars **vars);
void				built_cd(char **cmd);
void				built_env(char **g_env);
char				**get_entire_env(char **env);

//------------------------mini_utils.c------------------------//

int					invalid_input(char *str);
int		is_valid_var_name(char *name);
int		var_same(char *var_name, char *name);
t_vars	*built_unset(t_vars *head, char *var_delete);
void	unset_var_from_array(char **array, char *var_delete);
t_vars	*builtin_unset(char **args, t_vars *vars, char **env, char **g_env);

//-----------------------VARIABLES-----------------------------//

char	*get_var_name(char *str);
char	*get_var_value(char *str);
t_vars	*new_var_node(char *env_line);
void	vars_add_back(t_vars **head, t_vars *new);
t_vars	*init_vars_from_env(char **g_env);

#endif