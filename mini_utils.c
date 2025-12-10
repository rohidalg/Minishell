/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:47:01 by rohidalg          #+#    #+#             */
/*   Updated: 2025/12/10 18:21:01 by rohidalg         ###   ########.fr       */
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
			return (1);
		}
		i++;
	}
	return (0);
}

// en el subject pone "No interpretar comillas sin cerrar o caracteres 
// especiales no especificados en el enunciado como \ (barra invertida)
// o ; (punto y coma)." pero yo lo puse como que no ejecute nada,
// pero en la terminal normal simplemente la ignora literalmente 
// (echo hola\mundo holamundo) asi que tenngo que arreglar eso,
// y tambien que no se cierre la mini.