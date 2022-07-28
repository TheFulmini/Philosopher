/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:02:07 by afulmini          #+#    #+#             */
/*   Updated: 2022/01/19 22:29:37 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_rules	*free_forks(t_rules *sim)
{
	int	i;

	i = 0;
	if (sim->forks)
	{
		while (sim->forks[i])
		{
			pthread_mutex_destroy(&sim->forks[i]->lock);
			free(sim->forks[i]);
			i++;
		}
		free(sim->forks);
	}
	return (NULL);
}

t_rules	*free_philo(t_rules *sim)
{
	int	i;

	i = 0;
	if (sim->philo)
	{
		while (sim->philo[i])
			free(sim->philo[i++]);
		free(sim->philo);
	}
	return (NULL);
}

t_rules	*free_all(t_rules *sim)
{
	free_forks(sim);
	free_philo(sim);
	if (sim->data)
	{	
		if (sim->data->start)
			free(sim->data->start);
		free(sim->data);
	}
	free(sim);
	return (NULL);
}
