
#include "minishell.h"

void check_built_in(char *cmd, char **g_env)
{
	if (getenv("PATH") == NULL)
	{
		if (strcmp(cmd, "pwd") == 0)
			built_pwd();
		// else if (strcmp(cmd, "cd") == 0)
		// 	built_cd(cmd[1]);
		else if (strcmp(cmd, "exit") == 0)
			exit(EXIT_SUCCESS);
		else if (strcmp(cmd, "env") == 0)
			built_env(g_env);
	}
}

int	header(char **env, char **g_env)
{
	char *input;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)		// CTRL+D
			break ;

		if (*input)		// Si no está vacío
		{
			if (!invalid_input(input)) // Solo continúa si no hay caracteres prohibidos
			{
				check_built_in(input, g_env);
				add_history(input);
				run_pipex(input, env);
			}
		}
		free(input);
	}
	return (0);
}


void run_pipex(char *input, char **env)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		// Proceso hijo: ejecuta el comando
		ft_exec(input, env);
		exit(127);
	}
	else
	{
		// Proceso padre: espera a que termine el hijo para volver a la minishell
		waitpid(pid, &status, 0);
	}
}

int main(int argc, char **argv, char **env)
{
	char **g_env;

	(void)argc;
	(void)argv;
	g_env = NULL;
	g_env = get_entire_env(env);
	header(env, g_env);
	return (0);
}
