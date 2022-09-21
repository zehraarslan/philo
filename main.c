/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarslan <zarslan@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:35:10 by zarslan           #+#    #+#             */
/*   Updated: 2022/09/21 17:37:19 by zarslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_message(char *message)
{
	printf("%s", message);
	return (0);
}

int	check_arg(int argc, char **argv, t_table *table)
{
	if (!(argc == 5 || argc == 6))
		return (0);
	table->argc = argc;
	table->philo_num = my_atoi(argv[1]);
	table->death_time = my_atoi(argv[2]);
	table->eat_time = my_atoi(argv[3]);
	table->sleep_time = my_atoi(argv[4]);
	table->eat_num = 0;
	table->death_num = 0;
	if (argc == 6)
	{
		if (my_atoi(argv[5]) < 0)
			return (0);
		table->eat_num = my_atoi(argv[5]);
	}
	if (!(my_atoi(argv[1]) > 0 && my_atoi(argv[2]) > 0 && \
		my_atoi(argv[3]) > 0 && my_atoi(argv[4]) > 0))
		return (0);
	return (1);
}

void	destroy(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_num)
		pthread_mutex_destroy(&table->philos[i].right_fork);
	pthread_mutex_destroy(&table->death_check_mutex);
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->time_mutex);
}

int	main(int argc, char **argv)
{
	int		i;
	t_table	table;

	now_time();
	if (check_arg(argc, argv, &table) == 0)
	{
		error_message("Hatalı argüman girdiniz.\n");
		return (0);
	}
	pthread_mutex_init(&table.death_check_mutex, NULL);
	pthread_mutex_init(&table.eat_check_mutex, NULL);
	pthread_mutex_init(&table.write_mutex, NULL);
	pthread_mutex_init(&table.time_mutex, NULL);
	create_philos(&table);
	create_thread(&table);
	if (death_check(&table) == 0)
	{
		i = -1;
		while (++i < table.philo_num)
			pthread_join(table.philos[i].philo, NULL);
		destroy(&table);
		return (0);
	}
	return (0);
}
