/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:03:03 by afulmini          #+#    #+#             */
/*   Updated: 2022/01/20 09:30:37 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_msg(t_philo *philo, char *str, int mode)
{
	int	stamp;

	stamp = get_timestamp(philo->data->start);
	pthread_mutex_lock(&philo->data->write);
	if (!philo->data->dead || mode)
		printf("%d %d %s", stamp, philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
}

void	my_usleep(int ms)
{
	struct timeval	sleep;

	gettimeofday(&sleep, NULL);
	while (get_timestamp(&sleep) < ms)
		usleep(100);
}
