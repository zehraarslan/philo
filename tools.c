/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarslan <zarslan@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 01:29:03 by zarslan           #+#    #+#             */
/*   Updated: 2022/09/21 17:39:51 by zarslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	my_atoi(char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (str[i] <= 32)
		i++;
	if (str[i] == '-')
		return (-1);
	if (str[i] >= '0' && str[i] <= '9')
	{
		while (str[i])
		{
			num += str[i] - 48;
			if (str[i + 1])
				num *= 10;
			i++;
		}
	}
	else
		return (-1);
	return (num);
}

unsigned long long	now_time(void)
{
	struct timeval			tv;
	static unsigned long	first_time = 0;

	gettimeofday(&tv, NULL);
	if (first_time == 0)
		first_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - first_time);
}

void	my_usleep(int ms)
{
	unsigned long long	time;

	time = now_time();
	while (now_time() < time + ms)
	{
		usleep(1);
	}
}

void	write_case(char *message, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->write_mutex);
	pthread_mutex_lock(&(philo->table->death_check_mutex));
	if (philo->table->death_num == 0)
	{
		pthread_mutex_lock(&philo->table->time_mutex);
		printf("%lld %d %s\n", now_time(), philo->philo_id, message);
		pthread_mutex_unlock(&philo->table->time_mutex);
	}
	pthread_mutex_unlock(&(philo->table->death_check_mutex));
	pthread_mutex_unlock(&philo->table->write_mutex);
}
