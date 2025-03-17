/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:31:39 by mthodi            #+#    #+#             */
/*   Updated: 2025/03/17 11:11:59 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	#include "philo.h"

	int	is_philo_dead(t_philo *philo)
	{
		long	n_time;
		int		flag;

		flag = 0;
		ft_mutex(philo, 1);
		if (philo->philo_info->is_dead)
			flag = 1;
		else
		{
			n_time = n_timestamp(&philo->life_t);
			if ((n_time - philo->life) > (philo->philo_info->time_to_die))
			{
				ft_mutex(philo, 0);
				print_info(philo, 5);
				ft_mutex(philo, 1);
				philo->philo_info->is_dead = true;
				flag = 1;
			}
		}
		ft_mutex(philo, 0);
		return (flag);
	}

	static	void	init_info(t_philo *philo, int argc, char **argv)
	{
		philo->fork = 0;
		philo->m_fork = 0;
		philo->philo_info->time_to_die = ft_atoi(argv[2]);
		philo->philo_info->time_to_eat = ft_atoi(argv[3]);
		philo->philo_info->time_to_sleep = ft_atoi(argv[4]);
		pthread_mutex_init(&philo->lock, NULL);
		pthread_mutex_init(&philo->rlock, NULL);
		philo->philo_info->num_of_philo = ft_atoi(argv[1]);
		if (argc == 6)
			philo->times_to_eat = ft_atoi(argv[5]);
		else
			philo->times_to_eat = -1;
	}

	bool	init_philo(t_philo *philo, int argc, char **argv)
	{
		int		i;
		t_info	*philo_info;

		i = 0;
		philo_info = malloc(sizeof(t_info));
		if (!philo_info)
			return (false);
		philo_info->is_dead = false;
		pthread_mutex_init(&philo_info->print_lock, NULL);
		pthread_mutex_init(&philo_info->dlock, NULL);
		while (i < ft_atoi(argv[1]))
		{
			philo[i].philo_info = philo_info;
			philo[i].id = i + 1;
			init_info(&philo[i], argc, argv);
			gettimeofday(&philo[i].life_t, NULL);
			philo[i].life = n_timestamp(&philo[i].life_t);
			if (i == (ft_atoi(argv[1]) - 1))
				philo[i].next = &philo[0];
			else
				philo[i].next = &philo[i + 1];
			i++;
		}
		return (true);
	}

	int	ft_atoi(const char *str)
	{
		unsigned int	num;
		int				negative;

		num = 0;
		negative = 1;
		while (*str == ' ' || (*str >= 19 && *str <= 13))
			str++;
		if (*str == '-' || *str == '+')
		{
			if (*str == '-')
				negative = -negative;
			str++;
		}
		while (*str >= '0' && *str <= '9')
		{
			num = (num * 10) + (*str - '0');
			str++;
		}
		if (num > 2147483648 && negative == -1)
			return (0);
		if ((num > 2147483647 && negative == 1) || (*str || (str[0] == '+'
					&& !str[1]) || (str[0] == '-' && !str[1])))
			return (-1);
		str = NULL;
		return (num * negative);
	}

	bool	ft_error(int argc, char **argv)
	{
		int	i;

		if (argc < 5 || argc > 6)
		{
			printf("Error : Run ./philo 2 800 200 200\n");
			return (false);
		}
		i = 1;
		while (argv[i])
		{
			if (*argv[i] == '\0' || ft_atoi(argv[i]) <= 0)
			{
				printf("Error : Run ./philo 2 800 200 200\n");
				return (false);
			}
			i++;
		}
		return (true);
	}
