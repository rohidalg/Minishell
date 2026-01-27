/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 20:26:05 by wiljimen          #+#    #+#             */
/*   Updated: 2026/01/27 17:13:50 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_var_start(char c)
{
	return (c == '_' || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int	is_var_char(char c)
{
	return (is_var_start(c) || (c >= '0' && c <= '9'));
}

int	var_name_len(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && is_var_char(s[i]))
		i++;
	return (i);
}


