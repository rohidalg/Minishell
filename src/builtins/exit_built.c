/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:40:41 by rohidalg          #+#    #+#             */
/*   Updated: 2026/01/28 15:04:31 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_sign(char *s, int *i)
{
	int	sign;

	sign = 1;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static int	all_digits(char *s, int i)
{
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	parse_ll(char *s, long long *out)
{
	int					i;
	int					sign;
	unsigned long long	n;

	if (!s || !s[0])
		return (0);
	i = 0;
	sign = get_sign(s, &i);
	if (!s[i] || !all_digits(s, i))
		return (0);
	n = 0;
	while (s[i])
	{
		n = n * 10 + (s[i] - '0');
		if (sign == 1 && n > (unsigned long long)LLONG_MAX)
			return (0);
		if (sign == -1 && n > (unsigned long long)LLONG_MAX + 1ULL)
			return (0);
		i++;
	}
	*out = (long long)n * sign;
	return (1);
}

static int	exit_code(long long n)
{
	int	code;

	code = (int)(n % 256);
	if (code < 0)
		code += 256;
	return (code);
}

int	builtin_exit(char **args)
{
	long long	n;

	if (!args || !args[1])
		exit(g_exit_status);
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		g_exit_status = 1;
		return (1);
	}
	if (!parse_ll(args[1], &n))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(2);
	}
	exit(exit_code(n));
}
