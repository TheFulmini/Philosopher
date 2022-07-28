/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:02:54 by afulmini          #+#    #+#             */
/*   Updated: 2022/01/20 13:31:28 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_dead(t_philo *philo)
{
	int	astamp;

	astamp = get_timestamp(philo->data->start);
	if (astamp - philo->last_meal < philo->data->to_die
		|| philo->eaten == philo->data->max_meals)
		return (0);
	philo->data->dead = 1;
	print_msg(philo, "\033[31mhas died\033[0m\n", 1);
	return (1);
}

void	taking_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->left->lock);
	print_msg(philo, "has taken a fork\n", 0);
	pthread_mutex_lock(&philo->right->lock);
	print_msg(philo, "has taken a fork\n", 0);
}

int	eating(t_philo *philo)
{
	int	stamp;

	taking_fork(philo);
	if (!philo->data->dead)
	{	
		stamp = get_timestamp(philo->data->start);
		philo->last_meal = stamp;
		print_msg(philo, "\033[32mis eating\n\033[0m", 0);
		my_usleep(philo->data->to_eat);
		philo->eaten++;
	}
	pthread_mutex_unlock(&philo->left->lock);
	pthread_mutex_unlock(&philo->right->lock);
	return (0);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	if (philo->eaten == philo->data->max_meals)
		return (NULL);
	eating(philo);
	if (philo->eaten == philo->data->max_meals)
		return (NULL);
	if (!philo->data->dead)
	{
		print_msg(philo, "\033[35mis sleeping\n\033[0m", 0);
		my_usleep(philo->data->to_sleep);
	}
	if (!philo->data->dead)
		print_msg(philo, "\033[35mis thinking\n\033[0m", 0);
	if (!philo->data->dead)
		philo_routine(philo);
	return (NULL);
}
