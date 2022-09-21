/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarslan <zarslan@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:29:34 by zarslan           #+#    #+#             */
/*   Updated: 2022/09/21 17:40:00 by zarslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_table	t_table;
typedef struct s_philo
{
	int					philo_id;
	int					philo_eat_num;
	unsigned long long	last_meal_time;
	unsigned long long	death_time;
	int					eat_time;
	int					sleep_time;
	int					eat_num;
	int					*death_num;
	pthread_mutex_t		right_fork;
	pthread_mutex_t		*left_fork;
	pthread_t			philo;
	t_table				*table;
}	t_philo;

typedef struct s_table
{
	int					argc;
	int					philo_num;
	unsigned long long	death_time;
	int					eat_time;
	int					sleep_time;
	int					eat_num;
	int					death_num;
	pthread_mutex_t		death_check_mutex;
	pthread_mutex_t		eat_check_mutex;
	pthread_mutex_t		time_mutex;
	pthread_mutex_t		write_mutex;
	t_philo				philos[200];
}	t_table;

int					my_atoi(char *str);
unsigned long long	now_time(void);
void				my_usleep(int ms);
int					error_message(char *message);
t_philo				edit_philos(int i, t_table *table);
void				create_philos(t_table	*table);
int					create_thread(t_table *table);
int					death_check(t_table *table);
void				*lifecycle(void *tmp);
void				eat_cycle(t_philo *philo);
int					check_arg(int argc, char **argv, t_table *table);
void				write_case(char *message, t_philo *philo);
#endif