/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:48:58 by rohidalg          #+#    #+#             */
/*   Updated: 2026/01/21 22:37:08 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "pipex/pipex.h"
# include <errno.h>
# include <pthread.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

extern int			g_exit_status;

typedef struct s_vars
{
	char			*name;
	char			*value;
	struct s_vars	*next;
}					t_vars;

//------------------------parse.c------------------------//

int					header(char ***g_env, t_vars **vars);
void				run_pipex(char *input, char **g_env);

//------------------------BUILTS-IN------------------------//

int					check_built_in(char **cmd, char ***g_env, t_vars **vars);
void				unset_export_cd_echo(char **cmd, char ***g_env,
						t_vars **vars);
void				pwd_exit_env(char **cmd, char ***g_env);
void				builtin_pwd(void);
void				built_env(char **g_env);
char				**get_entire_env(char **env);
int					is_valid_var_name(char *name);
t_vars				*built_unset(t_vars *head, char *var_delete);
void				unset_var_from_array(char **array, char *var_delete);
t_vars				*builtin_unset(char **args, t_vars *vars, char **g_env);
char				**builtin_export(char **args, t_vars **vars_list,
						char **g_env);
void				print_exported(t_vars *vars_names);
void				sort_names(char **vars_names);
char				*vars_get_value(t_vars *vars, char *name);
void				cd_error(char *var);
char				*cd_choices(char **args, t_vars *vars);
char				*join_var(char *var, char *value);
void				set_var_both(char *line, t_vars **vars, char ***g_env);
int					cd_is_dash(char **args);
void				cd_chdir_fail(char *target);
char				**cd_update_pwds(t_vars **vars, char **g_env, char *oldpwd,
						char *newpwd);
char				**cd_ret(char *oldpwd, char *target, char *newpwd,
						char **g_env, int status);
char				**builtin_cd(char **args, t_vars **vars, char **g_env);
int					is_valid_n_flag(char *arg);
void				builtin_echo(char **args);
void				minishell_cleanup(char ***env, t_vars **vars);

//-----------------------VARIABLES-----------------------------//

int					var_same(char *var_name, char *name);
int					valid_var_name(char *var);
t_vars				*vars_find(t_vars *vars, char *name);
int					find_var(char *var_to_see, t_vars *vars_list);
void				vars_add_new(char *arg, t_vars **vars);
int					vars_set_if_exists(char *arg, t_vars *vars);
void				vars_mark_exported(char *name, t_vars **vars);
char				*get_var_name(char *str);
char				*get_var_value(char *str);
t_vars				*new_var_node(char *env_line);
void				vars_add_back(t_vars **head, t_vars *new);
t_vars				*init_vars_from_env(char **g_env);
char				**add_env_var(char *var, char **g_env);
int					env_replace(char *arg, char **g_env);
char				**env_set(char *arg, char **g_env);
int					vars_counter(t_vars *vars);
char				**vars_copy(t_vars *vars);

//------------------------SIGNALS-----------------------------//

void				handle_signals(void);
void				signals_handler(int sig);

//------------------------mini_utils.c------------------------//

int					invalid_input(char *str);

#endif