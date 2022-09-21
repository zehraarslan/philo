/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarslan <zarslan@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:16:12 by zarslan           #+#    #+#             */
/*   Updated: 2022/09/21 18:01:22 by zarslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death_write(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->death_check_mutex);
	philo->table->death_num = 1;
	pthread_mutex_unlock(&philo->table->death_check_mutex);
	if (philo->table->argc == 6)
	{
		pthread_mutex_lock(&philo->table->eat_check_mutex);
		if (philo->eat_num != philo->philo_eat_num)
		{
			printf("%lld %d philo died\n", now_time(), \
				philo->philo_id);
		}
		pthread_mutex_unlock(&philo->table->eat_check_mutex);
	}
	else
	{
		printf("%lld %d philo died\n", now_time(), philo->philo_id);
	}
	pthread_mutex_unlock(&philo->table->time_mutex);
}

int	death_check(t_table *table)
{
	int	i;
	int	death_control;

	pthread_mutex_lock(&table->death_check_mutex);
	death_control = table->death_num;
	pthread_mutex_unlock(&table->death_check_mutex);
	while (table->death_num == 0)
	{
		i = -1;
		while (++i < table->philo_num)
		{
			pthread_mutex_lock(&table->time_mutex);
			if (now_time() - table->philos[i].last_meal_time \
				> table->philos[i].death_time)
			{
				death_write(&table->philos[i]);
				return (0);
			}
			pthread_mutex_unlock(&table->time_mutex);
		}
		pthread_mutex_lock(&table->death_check_mutex);
		death_control = table->death_num;
		pthread_mutex_unlock(&table->death_check_mutex);
	}
	return (0);
}
