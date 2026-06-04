/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skucukon <skucukon@student.42istanbul.com.tr>  #+#      +:++#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-06-04 08:55:16 by skucukon          #+#    #+#             */
/*   Updated: 2026-06-04 08:55:16 by skucukon         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	single_philo_case(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_philosopher_status(philo, FORK);
	ft_usleep(philo->data->time_to_die + 10, philo->data);
	pthread_mutex_unlock(philo->left_fork);
	return (1);
}

int	take_up_the_forks(t_philo *philo)
{
	if (!is_sim_end(philo->data))
	{
		if (philo->data->number_of_philosophers == 1)
			return (single_philo_case(philo));
		else if (philo->id % 2)
		{
			pthread_mutex_lock(philo->right_fork);
			print_philosopher_status(philo, FORK);
			pthread_mutex_lock(philo->left_fork);
			print_philosopher_status(philo, FORK);
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			print_philosopher_status(philo, FORK);
			pthread_mutex_lock(philo->right_fork);
			print_philosopher_status(philo, FORK);
		}
		return (0);
	}
	return (1);
}

void	put_down_the_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

int	eat(t_philo *philo)
{
	if (!is_sim_end(philo->data))
	{
		print_philosopher_status(philo, EATING);
		pthread_mutex_lock(&philo->mutex_meal);
		philo->number_of_eaten_meals++;
		philo->time_of_last_eaten_meal = get_time_ms();
		pthread_mutex_unlock(&philo->mutex_meal);
		ft_usleep(philo->data->time_to_eat, philo->data);
		return (0);
	}
	return (1);
}

void	sleep_and_think(t_philo *philo)
{
	print_philosopher_status(philo, SLEEPING);
	ft_usleep(philo->data->time_to_sleep, philo->data);
	print_philosopher_status(philo, THINKING);
}
