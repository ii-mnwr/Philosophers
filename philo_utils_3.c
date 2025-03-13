/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:31:49 by mthodi            #+#    #+#             */
/*   Updated: 2024/08/25 16:07:02 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_mutex(t_philo *philo, int lock_flag)
{
	if (lock_flag)
		pthread_mutex_lock(&philo->philo_info->dlock);
	else
		pthread_mutex_unlock(&philo->philo_info->dlock);
}

void	lock_order(t_philo *philo)
{
	if (philo->id % philo->philo_info->num_of_philo)
	{
		pthread_mutex_lock(&philo->lock);
		pthread_mutex_lock(&philo->next->lock);
	}
	else
	{
		pthread_mutex_lock(&philo->next->lock);
		pthread_mutex_lock(&philo->lock);
	}
}

long	n_timestamp(struct timeval *time)
{
	struct timeval	c_time;
	long			res;

	gettimeofday(&c_time, NULL);
	res = ((c_time.tv_sec - time->tv_sec) * 1000) + ((c_time.tv_usec
				- time->tv_usec) / 1000);
	return (res);
}

size_t	timestamp_new(void)
{
	struct timeval	c_time;
	size_t			time;

	gettimeofday(&c_time, NULL);
	time = (c_time.tv_sec * 1000000 + c_time.tv_usec);
	return (time);
}
