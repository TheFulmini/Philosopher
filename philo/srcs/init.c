/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:02:26 by afulmini          #+#    #+#             */
/*   Updated: 2022/01/20 10:58:34 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_rules	*create_sim(void)
{
	t_rules	*sim;

	sim = malloc(sizeof(t_rules));
	if (!sim)
		return (NULL);
	sim->philo = NULL;
	sim->forks = NULL;
	return (sim);
}

t_rules	*init_forks(t_rules *sim)
{
	int	i;

	i = 0;
	sim->forks = malloc(sizeof(t_fork *) * (sim->data->nbr + 1));
	if (!sim->forks)
		return (free_all(sim));
	while (i < sim->data->nbr)
	{
		sim->forks[i] = malloc(sizeof(t_fork));
		if (!sim->forks[i])
			return (free_all(sim));
		pthread_mutex_init(&sim->forks[i]->lock, NULL);
		i++;
	}
	sim->forks[i] = NULL;
	return (sim);
}

t_rules	*init_philo(t_rules *sim)
{
	int	i;

	i = 0;
	sim->philo = malloc(sizeof(t_philo *) * (sim->data->nbr + 1));
	if (!sim->philo)
		return (free_all(sim));
	while (i < sim->data->nbr)
	{
		sim->philo[i] = malloc(sizeof(t_philo));
		if (!sim->philo[i])
			return (free_all(sim));
		sim->philo[i]->id = i + 1;
		sim->philo[i]->eaten = 0;
		sim->philo[i]->last_meal = 0;
		if (i == 0)
			sim->philo[i]->left = sim->forks[sim->data->nbr - 1];
		else
			sim->philo[i]->left = sim->forks[i - 1];
		sim->philo[i]->right = sim->forks[i];
		sim->philo[i]->data = sim->data;
		i++;
	}
	sim->philo[i] = NULL;
	return (sim);
}

t_rules	*init_rules(int argc, char **argv, t_rules *sim)
{
	sim->data = malloc(sizeof(t_data));
	if (!sim->data)
		return (free_all(sim));
	sim->data->start = malloc(sizeof(struct timeval));
	if (!sim->data->start)
		return (free_all(sim));
	sim->data->nbr = ft_atoi(argv[1]);
	sim->data->to_die = ft_atoi(argv[2]);
	sim->data->to_eat = ft_atoi(argv[3]);
	sim->data->to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		sim->data->max_meals = ft_atoi(argv[5]);
	else
		sim->data->max_meals = -1;
	pthread_mutex_init(&sim->data->write, NULL);
	if (!init_forks(sim))
		return (NULL);
	if (!init_philo(sim))
		return (NULL);
	return (sim);
}
