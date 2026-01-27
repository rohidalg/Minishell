/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:24:05 by rohidalg          #+#    #+#             */
/*   Updated: 2026/01/27 16:54:37 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>

//------------------------pipex.c------------------------//

void	ft_exit(char *str, int ex);
char	*ft_getenv(char *name, char **env);
char	*ft_getpath(char *command, char **env);
void	ft_son(char **argv, char **env, int *fd_p);
void	ft_father(char **argv, char **env, int *fd_p);

//------------------------ft_utils.c------------------------//

void	ft_check_argv(int argc, char **argv);
char	*ft_check_path(char **path, char *cmd);
int		ft_file(char *file, int option);
void	ft_exec(char *command, char **env);

//------------------------redirects.c------------------------//

int		redirect_input(char *file);
int		redirect_output(char *file, int append);

//------------------------env_check.c------------------------//

char	**prepare_args(char **args);
void	apply_quotes(char **args, char **env);
char	*expand_in_quotes(const char *str, char **env);
char	*ft_quotes(const char *str, char **env);

//------------------------redirects.c------------------------//

char	**redirect(char **args);

#endif