
#include "minishell.h"

// void	ft_signal(int sig)
// {
// 	g_signal = sig; // actualiza la global
// }

void	check_built_in(char *cmd, char **envp)
{
	if (getenv("PATH") == NULL)
	{
		if (strcmp(cmd, "pwd") == 0)
			built_pwd();
		else if (strcmp(cmd, "cd") == 0)
			built_cd(cmd[1]);
		else if (strcmp(cmd, "exit") == 0)
			exit(EXIT_SUCCESS);
		else if (strcmp(cmd, "env") == 0)
			built_env(envp);
	}
}

int	header(char **envp, char **env)
{
	char	*input; // puntero para guardar lo que se escribe
	while (1)
	{
		input = readline("minishell> "); // muestra "minishell> " y espera input
		check_built_in(input, envp);
		if (!input)
			// si el usuario pulsa Ctrl+D (EOF),salimos
			break ;
		else if (*input) // si la línea no está vacía (no es solo Enter)
		{
			add_history(input); // guarda el comando en el historial
			run_pipex(input, env);
		}
		free(input);
	}
	return (0);
}

void	run_pipex(char *input, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
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

int	main(int argc, char **argv, char **env, char **envp)
{
	(void)argc;
	(void)argv;
	header(env, envp);
	return (0);
}
// AVANZAR CON EL TEMA DE LAS COMILLAS
