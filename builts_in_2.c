#include "minishell.h"

void    built_cd(char **cmd)
{
    if (cmd[1] == NULL)
        chdir(getenv("HOME"));
    else if(cmd[1] != 0)
        perror("cd");
}

char	**get_entire_env(char **env)
{
	int i;
	int j;
	char *sub;
	char **new_env;

	i = 0;
	if (!*env)
		exit(EXIT_FAILURE);
	while(env[i])
		i++;
	new_env = ft_calloc(i, sizeof(char));
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
			j++;
		sub = ft_substr(env[i], 0, j);
		free(sub);
		i++;
	}
	return (new_env);
}

void	built_pwd(void)
{
	char *cwd;

	cwd = malloc(1024);
	if (!cwd)
	{
		free(cwd);
		exit(EXIT_FAILURE);
	}
    if (getcwd(cwd, 1024) != NULL)
		printf("%sAA\n", cwd);
	else
		perror("pwd");
	free(cwd);
}

void	built_env(char **g_env)
{
	int	i;

	i = 0;
	while (g_env[i])
	{
		printf("%s\n", g_env[i]);
		i++;
	}
}

// void	built_unset()

// int main(int argc, char **argv, char **env)
// {
// 	(void)argv;
// 	(void)argc;

// 	char **g_env = get_entire_env(env);
//     built_env(g_env);
//     return (0);
// }