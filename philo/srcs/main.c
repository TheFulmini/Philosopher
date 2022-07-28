/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:02:34 by afulmini          #+#    #+#             */
/*   Updated: 2022/01/20 11:22:28 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_timestamp(struct timeval *start)
{
	struct timeval		now;
	int					startms;
	int					nowms;
	int					ret;

	gettimeofday(&now, NULL);
	startms = (start->tv_usec / 1000) + (start->tv_sec * 1000);
	nowms = (now.tv_usec / 1000) + (now.tv_sec * 1000);
	ret = nowms - startms;
	return (ret);
}

int	check_if_done(t_rules *sim)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < sim->data->nbr)
	{
		if (sim->philo[i]->eaten == sim->data->max_meals)
			ret++;
		i++;
	}
	return (ret);
}

void	create_thd(t_rules *sim)
{
	int	i;

	i = 0;
	while (i < sim->data->nbr)
	{
		pthread_create(&sim->philo[i]->tid, NULL, philo_routine, sim->philo[i]);
		pthread_detach(sim->philo[i]->tid);
		usleep(100);
		i++;
	}
}

int	philo(t_rules *sim)
{
	int	i;

	sim->data->dead = 0;
	sim->data->done = 0;
	gettimeofday(sim->data->start, NULL);
	create_thd(sim);
	while (!sim->data->dead)
	{
		i = 0;
		sim->data->done = check_if_done(sim);
		if (sim->data->done == sim->data->nbr)
		{
			printf("All philos ate %d tim(s).\n", sim->data->max_meals);
			break ;
		}
		while (i < sim->data->nbr)
		{
			my_usleep(1);
			if (!sim->data->dead)
				sim->data->dead = check_dead(sim->philo[i]);
			i++;
		}
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_rules	*sim;

	if (argc < 5 || argc > 6)
	{
		write(0, "Usage Error\n", 13);
		return (1);
	}
	if (!check_arg(argv))
		return (1);
	if (!check_zero(argv))
		return (1);
	sim = create_sim();
	if (!sim)
		return (1);
	if (!init_rules(argc, argv, sim))
		return (1);
	philo(sim);
	free_all(sim);
	return (0);
}
