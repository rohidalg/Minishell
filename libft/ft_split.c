/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:40:41 by rohidalg          #+#    #+#             */
/*   Updated: 2025/10/13 19:37:51 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	skip_quotes(const char *str, int *i)
{
	char	quote;
	int		len;

	quote = str[*i];
	len = 1;          
	(*i)++;
	while (str[*i] && str[*i] != quote)
	{
		(*i)++;
		len++;
	}
	if (str[*i] == quote)
	{
		(*i)++;
		len++;       
	}
	else
	{
		fprintf(stderr, "Error: comilla %c sin cerrar\n", quote);
		exit(EXIT_FAILURE);
	}
	return (len);
}


int	ft_countwords(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (!str[i])
			break ;
		if (str[i] == '\'' || str[i] == '"')
			skip_quotes(str, &i);
		else
			while (str[i] && str[i] != c && str[i] != '\'' && str[i] != '"')
				i++;
		count++;
	}
	return (count);
}


char	*ft_words(const char *str, char c, int *i)
{
	int		start;
	int		len;
	char	*word;

	while (str[*i] == c)
		(*i)++;
	if (!str[*i])
		return (NULL);
	start = *i;
	if (str[*i] == '\'' || str[*i] == '"')
		len = skip_quotes(str, i);
	else
		while (str[*i] && str[*i] != c)
			(*i)++;
	len = *i - start;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, str + start, len + 1);
	return (word);
}


char	**ft_free(char **string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		free(string[i]);
		i++;
	}
	free(string);
	return (0);
}

char	**ft_split(char const *str, char c)
{
	int		countwords;
	char	**string;
	int		i_string;
	int		i;

	if (!str)
		return (0);
	countwords = ft_countwords(str, c);
	string = ft_calloc(countwords + 1, sizeof(char *));
	if (!string)
		return (0);
	i = 0;
	i_string = 0;
	while (i_string < countwords)
	{
		string[i_string] = ft_words(str, c, &i);
		if (!string[i_string])
			return (ft_free(string));
		i_string++;
	}
	string[i_string] = NULL;
	return (string);
}


/*cuenta palabras utilizando el delimitador c,
y count se imcrementa cada vez que encuentra el primer caracter de la palabra*/

/*i rastrea la posicion de la palabra y len coge el tamaño
para el espacio de memoria*/

/*libera memoria asiganada en bucle para las string y luego para la matriz*/

/*asigno memoria con calloc y sabiendo las palabras que hay, hago el tamaño,
luego con ft_words las agrega a la matriz, y en caso de error uso el free*/
