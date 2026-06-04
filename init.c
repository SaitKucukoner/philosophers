/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skucukon <skucukon@student.42istanbul.com.tr>  #+#      +:++#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-06-04 08:09:46 by skucukon          #+#    #+#             */
/*   Updated: 2026-06-04 08:09:46 by skucukon         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_of_must_eat_each = ft_atoi(argv[5]);
	else
		data->number_of_must_eat_each = -1;
	data->threads_ready_to_start = 0;
	data->is_sim_end = 0;
	data->time_of_sim_start = 0;
	pthread_mutex_init(&data->mutex_thread_start, NULL);
	pthread_mutex_init(&data->mutex_print, NULL);
	pthread_mutex_init(&data->mutex_sim_end, NULL);
	return (0);
}

int	init_forks(t_data *data)
{
	size_t	i;
	size_t	number_of_philo;

	i = 0;
	number_of_philo = data->number_of_philosophers;
	data->mutex_fork = malloc(sizeof(pthread_mutex_t) * number_of_philo);
	if (!data->mutex_fork)
		return (1);
	while (i < number_of_philo)
	{
		pthread_mutex_init(&data->mutex_fork[i], NULL);
		i++;
	}
	return (0);
}

int	init_philosophers(t_data *data)
{
	size_t	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philos)
		return (1);
	while (i < data->number_of_philosophers)
	{
		data->philos[i].id = i + 1;
		data->philos[i].number_of_eaten_meals = 0;
		data->philos[i].time_of_last_eaten_meal = 0;
		data->philos[i].data = data;
		pthread_mutex_init(&data->philos[i].mutex_meal, NULL);
		data->philos[i].left_fork = &data->mutex_fork[i];
		data->philos[i].right_fork = &data->mutex_fork[(i + 1)
			% data->number_of_philosophers];
		i++;
	}
	return (0);
}
