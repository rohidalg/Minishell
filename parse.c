#include "minishell.h"

void	ft_signal(int sig)
{
	g_signal = sig; // actualiza la global
}

int	header(char **env)
{
	char *input; // puntero para guardar lo que se escribe
	while (1)
	{
		input = readline("minishell> "); // muestra "minishell> " y espera input
		if (!input)
			// si el usuario pulsa Ctrl+D (EOF),salimos
			break ;
		if (strcmp(input, "exit") == 0) // si el usuario escribe "exit", salimos
		{
			free(input);
			break ;
		}
		if (*input) // si la línea no está vacía (no es solo Enter)
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

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	header(env);
	return (0);
}


// AVANZAR CON EL TEMA DE LAS COMILLAS
