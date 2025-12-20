/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:24:05 by rohidalg          #+#    #+#             */
/*   Updated: 2025/12/20 17:24:22 by wiljimen         ###   ########.fr       */
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

typedef struct s_vars
{
	char			*name;
	char			*value;
	struct s_vars	*next;
}					t_vars;

// Name es el nombre de la variable, y Value el valor (Rodrigo=Bello)

//------------------------parse.c------------------------//

int					header(char **g_env, t_vars **vars);
void				run_pipex(char *input, char **g_env);

//------------------------BUILTS-IN------------------------//

void				built_pwd(void);
void				check_built_in(char **cmd, char ***g_env, t_vars **vars);
void				built_cd(char **cmd);
void				built_env(char **g_env);
char				**get_entire_env(char **env);
int					is_valid_var_name(char *name);
int					var_same(char *var_name, char *name);
t_vars				*built_unset(t_vars *head, char *var_delete);
void				unset_var_from_array(char **array, char *var_delete);
t_vars				*builtin_unset(char **args, t_vars *vars, char **g_env);
char				**builtin_export(char **args, t_vars **vars_list, char **g_env);
int					valid_var_name(char *var);
t_vars				*vars_find(t_vars *vars, char *name);
int					find_var(char *var_to_see, t_vars *vars_list);
void				vars_add_new(char *arg, t_vars **vars);
int					vars_set_if_exists(char *arg, t_vars *vars);
void				vars_mark_exported(char *name, t_vars **vars);

//-----------------------VARIABLES-----------------------------//

char				*get_var_name(char *str);
char				*get_var_value(char *str);
t_vars				*new_var_node(char *env_line);
void				vars_add_back(t_vars **head, t_vars *new);
t_vars				*init_vars_from_env(char **g_env);
char				**add_env_var(char *var, char **g_env);
int					env_replace(char *arg, char **g_env);
char				**env_set(char *arg, char **g_env);


//------------------------mini_utils.c------------------------//

int					invalid_input(char *str);

#endif