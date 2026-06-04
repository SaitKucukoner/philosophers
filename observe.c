/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skucukon <skucukon@student.42istanbul.com.tr>  #+#      +:++#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-06-04 08:28:12 by skucukon          #+#    #+#             */
/*   Updated: 2026-06-04 08:28:12 by skucukon         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_someone_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_meal);
	if (get_time_ms() - philo->time_of_last_eaten_meal
		>= philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->mutex_meal);
		pthread_mutex_lock(&philo->data->mutex_sim_end);
		philo->data->is_sim_end = 1;
		pthread_mutex_unlock(&philo->data->mutex_sim_end);
		print_philosopher_status(philo, DIED);
		return (1);
	}
	pthread_mutex_unlock(&philo->mutex_meal);
	return (0);
}

int	did_philo_eat_mimimum(t_philo *philo)
{
	long	tmp;

	tmp = philo->data->number_of_must_eat_each;
	if (tmp == -1)
		return (1);
	pthread_mutex_lock(&philo->mutex_meal);
	if (philo->number_of_eaten_meals >= (size_t)tmp)
	{
		pthread_mutex_unlock(&philo->mutex_meal);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&philo->mutex_meal);
		return (1);
	}
}

int	did_all_philos_eat_minimum(t_data *data, size_t total_of_each)
{
	if (total_of_each == data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->mutex_sim_end);
		data->is_sim_end = 1;
		pthread_mutex_unlock(&data->mutex_sim_end);
		return (0);
	}
	return (1);
}

void	*observer_process(void *arg)
{
	size_t	i;
	size_t	all_meals_eaten_each;
	t_data	*data;

	data = arg;
	while (1)
	{
		i = 0;
		all_meals_eaten_each = 0;
		while (i < data->number_of_philosophers)
		{
			if (is_someone_dead(&data->philos[i]))
				return (NULL);
			if (!did_philo_eat_mimimum(&data->philos[i]))
				all_meals_eaten_each++;
			i++;
		}
		if (!did_all_philos_eat_minimum(data, all_meals_eaten_each))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}
