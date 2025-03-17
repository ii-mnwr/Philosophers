/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:31:25 by mthodi            #+#    #+#             */
/*   Updated: 2025/03/16 12:40:24 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_info(t_philo *philo, int print_order)
{
	ft_mutex(philo, 1);
	if (!philo->philo_info->is_dead)
	{
		pthread_mutex_lock(&philo->philo_info->print_lock);
		printf("%ld ", n_timestamp(&philo->life_t));
		printf("%d", philo->id);
		if (print_order == 1)
			printf(" has taken a fork\n");
		else if (print_order == 2)
			printf(" is eating\n");
		else if (print_order == 3)
			printf(" is sleeping\n");
		else if (print_order == 4)
			printf(" is thinking\n");
		else if (print_order == 5)
		{
			printf(" died\n");
			philo->philo_info->is_dead = true;
		}
		pthread_mutex_unlock(&philo->philo_info->print_lock);
	}
	ft_mutex(philo, 0);
}

static bool	check_mirror_fork(t_philo *philo)
{
	if (philo->m_fork == philo->id || philo->next->m_fork == philo->id)
		return (true);
	return (false);
}

static void	*routine(void *philo_data)
{
	t_philo	*philo;

	philo = (t_philo *)philo_data;
	while (philo->philo_info->num_of_philo == 1)
		return (ft_single_philo(philo, philo->philo_info->time_to_die));
	while (1)
	{
		if (is_philo_dead(philo) || !philo->times_to_eat)
			break ;
		lock_order(philo);
		pthread_mutex_lock(&philo->rlock);
		if (!(philo->fork) && !(philo->next->fork)
			&& philo->times_to_eat && !check_mirror_fork(philo))
			if (!philo_eat(philo))
				return (NULL);
		pthread_mutex_unlock(&philo->rlock);
		pthread_mutex_unlock(&philo->lock);
		pthread_mutex_unlock(&philo->next->lock);
		usleep(100);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo	philo[MAX_PHILOS];
	int		i;

	i = 0;
	if (!ft_error(argc, argv))
		return (1);
	if (!init_philo(philo, argc, argv))
		return (1);
	while (i < ft_atoi(argv[1]))
	{
		pthread_create(&philo[i].thread, NULL, routine, (void *)&philo[i]);
		usleep(100);
		i++;
	}
	i = -1;
	while (++i < ft_atoi(argv[1]))
		pthread_join(philo[i].thread, NULL);
	free(philo->philo_info);
	return (0);
}
