#include "minishell.h"

void    built_cd(char **cmd)
{
    if (cmd[1] == NULL)
        chdir(getenv("HOME"));
    else if(cmd[1] != 0)
        perror("cd");
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

void	built_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

// int main(int argc, char **argv, char **envp)
// {
// 	(void)argv;
// 	(void)argc;
//     built_env(envp);
//     return (0);
// }
// Probando, hay que verificar todas las opciones, directorio anterior con .. y con -, directorio actual.