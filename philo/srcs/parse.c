/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:02:44 by afulmini          #+#    #+#             */
/*   Updated: 2022/01/20 09:30:37 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_isdigit(int c)
{
	if (48 <= c && c <= 57)
		return (1);
	return (0);
}

int	check_arg(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				write(0, "Error:\noptions must be valid numbers\n", 38);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_zero(char **av)
{
	int	i;
	int	n;

	i = 1;
	while (av[i] && i < 5)
	{
		n = ft_atoi(av[i]);
		if (n <= 0)
		{
			write(0, "Error:\noptions must be valid numbers\n", 38);
			return (0);
		}
		i++;
	}
	return (1);
}
