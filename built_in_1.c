/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:34:58 by wiljimen          #+#    #+#             */
/*   Updated: 2025/10/09 19:52:42 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	built_unset(t_vars **variables, char *namev)
// {
// 	t_vars	*previous;
// 	t_vars	*current;
// 	pid_t	child;
	
// 	previous = NULL;
// 	current = *variables;

// 	while (current->name != NULL)
// 	{
// 		if (current->name == namev)
// 		{
// 			if (previous == NULL)
// 				variables = current->next;
// 			else
// 				previous->next = current->next;
// 			free(current->name);
// 			free(current->value);
// 		}
// 		current->name;
// 	}
// }

// Terminar unsets, buscar explicación y entender mejor la lógica.