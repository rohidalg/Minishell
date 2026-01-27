/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:48:58 by rohidalg          #+#    #+#             */
/*   Updated: 2026/01/27 18:25:49 by rohidalg         ###   ########.fr       */
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

typedef struct s_exp
{
	char	**env;
	int		last;
	char	q;
}	t_exp;


typedef struct s_pipe_data
{
	char			**cmds;
	pid_t			*pids;
	int				n;
	int				i;
	int				prev;
	int				fd[2];
}					t_pipe_data;

typedef struct s_stage
{
	int				prev;
	int				fd[2];
	int				last;
	char			*cmd;
	char			**env;
}					t_stage;

//------------------------PARSING------------------------//

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
char				**builtin_cd(char **args, t_vars **vars, char **g_env);
void				builtin_echo(char **args);
void				minishell_cleanup(char ***env, t_vars **vars);

//-----------------------VARIABLES-----------------------------//

int					var_same(char *var_name, char *name);
int					valid_var_name(char *var);
t_vars				*vars_find(t_vars *vars, char *name);
t_vars				*find_var_helper(t_vars *lst, char *name);
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
char				*ft_getpath(char *cmd, char **env);

//------------------------SIGNALS-----------------------------//

void				handle_signals(void);
void				signals_handler(int sig);

//--------------------------QUOTES----------------------------//

int					invalid_input(char *str);
char				*remove_quotes(const char *s);
char				**split_quote_aware(const char *s);

//------------------------EXPANSOR----------------------------//

const char			*get_env_value(const char *var, char **g_env);
int					is_var_start(char c);
int					is_var_char(char c);
int					var_name_len(const char *s);
char				*expand_string(const char *s, char **env, int last);
void				expand_args(char **args, char **env, int last);
void				expand_args_skip(char **args, char **env, int last);
void				run_exec_args(char **args, char **g_env);
int					exec_error(char *cmd);
char				*append_char(char *s, char c);
char				*expansor_exit(char *out, int *i, int last);
char				*expansor_var(char *out, const char *s, int *i, char **g_env);

//------------------------PIPE_ENTRY------------------------------//

void				run_line(char *input, char **env);
void				run_pipeline(char *input, char **env);

//------------------------PIPE_SYNTAX------------------------------//

int					has_pipe(char *s);
int					pipe_syntax_str(char *s);

//------------------------PIPE_TRIM------------------------------//

int					array_len(char **a);
void				trim_all(char **cmds);

//------------------------PIPE_RUNTIME------------------------------//

void				wait_pids(pid_t *p, int n);
void				child_stage(t_stage st);

//------------------------PIPE------------------------------//

void				cleanup_pipeline(t_pipe_data *d, int started);
int					pipeline_prepare(t_pipe_data *d, char *input);

#endif