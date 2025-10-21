/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:47:01 by rohidalg          #+#    #+#             */
/*   Updated: 2025/10/21 18:50:13 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	invalid_input(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' || str[i] == ';')
		{
			fprintf(stderr, "Error: caracter no permitido '%c'\n", str[i]);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (0);
}

// en el subject pone "No interpretar comillas sin cerrar o caracteres especiales no especificados en el
// enunciado como \ (barra invertida) o ; (punto y coma)." pero yo lo puse como que no ejecute nada,
// pero en la terminal normal simplemente la ignora literalmente (echo hola\mundo
// holamundo) asi que tenngo que arreglar eso,
// y tambien que no se cierre la mini.

// char	*expand_dolar(const char *str, char **env)
// {
// 	int		i;
// 	int		start;
// 	char	*name;
// 	char	*env_name;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 			i++;
// 		start = i;
// 		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
// 			i++;
// 		if (i == start)
// 			return (0);
// 		name = ft_substr(str, start, i - start);
// 		env_name = ft_getenv(name, env);
// 	}
// 	return (env_name);
// }

// Cambia esto por tu variable global de estado de salida
// extern int	g_exit_status;

// int	is_in_single_quotes(const char *str)
// {
// 	int	i;
// 	int	simple;

// 	i = 0;
// 	simple = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
// 			simple = !simple;
// 		i++;
// 	}
// 	return (simple);
// }

// char	*get_env_value(const char *var)
// {
// 	char	*val;

// 	if (!var || !*var)
// 		return (ft_strdup(""));
// 	val = getenv(var);
// 	if (val)
// 		return (ft_strdup(val));
// 	return (ft_strdup(""));
// }

// char	*expand_env_vars(const char *str)
// {
// 	int		i;
// 	char	*result;
// 	char	*temp;
// 	char	*var;
// 	char	*value;
// 	int		start;
// 			char buf[2];

// 	result = ft_strdup("");
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			i++;
// 			if (str[i] == '?')
// 			{
// 				value = ft_itoa(g_exit_status);
// 				temp = ft_strjoin(result, value);
// 				free(result);
// 				free(value);
// 				result = temp;
// 				i++;
// 			}
// 			else if (ft_isalpha(str[i]) || str[i] == '_')
// 			{
// 				start = i;
// 				while (ft_isalnum(str[i]) || str[i] == '_')
// 					i++;
// 				var = ft_substr(str, start, i - start);
// 				value = get_env_value(var);
// 				temp = ft_strjoin(result, value);
// 				free(result);
// 				free(var);
// 				free(value);
// 				result = temp;
// 			}
// 			else
// 			{
// 				// Si no hay variable válida, añadimos el '$' literal
// 				temp = ft_strjoin(result, "$");
// 				free(result);
// 				result = temp;
// 			}
// 		}
// 		else
// 		{
// 			buf[0] = str[i];
// 			buf[1] = '\0';
// 			temp = ft_strjoin(result, buf);
// 			free(result);
// 			result = temp;
// 			i++;
// 		}
// 	}
// 	return (result);
// }

// char	**expand_tokens(char **tokens)
// {
// 	int		i;
// 	char	*expanded;

// 	i = 0;
// 	while (tokens[i])
// 	{
// 		if (!is_in_single_quotes(tokens[i]) && ft_strchr(tokens[i], '$'))
// 		{
// 			expanded = expand_env_vars(tokens[i]);
// 			free(tokens[i]);
// 			tokens[i] = expanded;
// 		}
// 		i++;
// 	}
// 	return (tokens);
// }
