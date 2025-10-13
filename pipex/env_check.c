#include "pipex.h"


char	*expand_dolar(const char *str, char **env)
{
	int		i;
	int		start;
	
	i = 0;
	if (!str)
		return (0);
	if (str[i] == '"')
	{
		start = ++i;
		while (str[i] && str[i] != '"')
		i++;
		return (ft_substr(str, start, i - start));
	}
	while(str[i])
	{
		if (str[i] == '$')
		{
			start = ++i;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
			return (ft_getenv(ft_substr(str, start, i - start), env));
		}
		i++;
	}
	return (ft_strdup(str));
}

// 	ARREGLAR CUANDO USO LAS COMILLAS SIMPLES Y EL $ SOLO SE ENVIA EL DOLAR

// int	skip_quotes(const char *str, int *i, int *start)
// {
// 	char	quote;
// 	int		len;

// 	if (str[*i] == '\'' || str[*i] == '"')
// 	{
// 		quote = str[*i];
// 		(*i)++;
// 		*start = *i;
// 		while (str[*i] && str[*i] != quote)
// 			(*i)++;
// 		len = *i - *start;
// 		if (str[*i] == quote)
// 			(*i)++;
// 		else
// 		{
// 			fprintf(stderr, "Error: comilla %c sin cerrar\n", quote);
// 			exit(EXIT_FAILURE);
// 		}
// 		return (len);
// 	}
// 	return (-1);
// }

// char *ft_getenv(char *name, char **env)
// {
// 	int i;
// 	int j;
// 	char *sub;

// 	i = 0;
// 	if (!*env)
// 		exit(EXIT_FAILURE);
// 	while (env[i])
// 	{
// 		j = 0;
// 		while (env[i][j] && env[i][j] != '=')
// 			j++;
// 		sub = ft_substr(env[i], 0, j);
// 		if (ft_strcmp(sub, name) == 0)
// 		{
// 			free(sub);
// 			return (env[i] + j + 1);
// 		}
// 		free(sub);
// 		i++;
// 	}
// 	return (0);
// }
// // busca la variable del entorno que deseemmos y nos devuelve su valor

// char *ft_getpath(char *command, char **env)
// {
// 	int i;
// 	char **path;
// 	char *tmp;
// 	char *path_part;
// 	char **cmmd;

// 	i = -1;
// 	path = ft_split(ft_getenv("PATH", env), ':');
// 	cmmd = ft_split(command, ' ');
// 	while (path[i++])
// 	{
// 		tmp = ft_strjoin(path[i], "/");			// "/usr/bin/"
// 		path_part = ft_strjoin(tmp, cmmd[0]); // "/usr/bin/ls"
// 		free(tmp);
// 		if (access(path_part, F_OK | X_OK) == 0) // existe? | ejecutable?
// 		{
// 			ft_free(cmmd);
// 			return (path_part);
// 		}
// 		free(path_part);
// 	}
// 	ft_free(path);
// 	ft_free(cmmd);
// 	return (command);
// }