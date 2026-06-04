/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skucukon <skucukon@student.42istanbul.com.tr>  #+#      +:++#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-06-04 08:51:20 by skucukon          #+#    #+#             */
/*   Updated: 2026-06-04 08:51:20 by skucukon         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_atoi(char *argument)
{
	int		i;
	size_t	result;

	i = 0;
	result = 0;
	while (argument[i] == ' ' || argument[i] == '\t')
		i++;
	if (argument[i] == '+')
		i++;
	while (argument[i] && ('0' <= argument[i] && argument[i] <= '9'))
	{
		result = (result * 10) + (argument[i] - '0');
		i++;
	}
	return (result);
}

size_t	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	is_sim_end(t_data *data)
{
	int	val;

	pthread_mutex_lock(&data->mutex_sim_end);
	val = data->is_sim_end;
	pthread_mutex_unlock(&data->mutex_sim_end);
	return (val);
}

void	ft_usleep(size_t duration_ms, t_data *data)
{
	size_t	start_time;

	start_time = get_time_ms();
	while (get_time_ms() - start_time < duration_ms)
	{
		if (is_sim_end(data))
			break ;
		usleep(50);
	}
}

void	print_philosopher_status(t_philo *philo, t_philo_status status)
{
	size_t	timestamp_in_ms;

	pthread_mutex_lock(&philo->data->mutex_print);
	timestamp_in_ms = get_time_ms() - philo->data->time_of_sim_start;
	if (is_sim_end(philo->data) && status != DIED)
	{
		pthread_mutex_unlock(&philo->data->mutex_print);
		return ;
	}
	if (status == DIED)
		printf("%zu %zu died\n", timestamp_in_ms, philo->id);
	else if (status == FORK)
		printf("%zu %zu has taken a fork\n", timestamp_in_ms, philo->id);
	else if (status == EATING)
		printf("%zu %zu is eating\n", timestamp_in_ms, philo->id);
	else if (status == SLEEPING)
		printf("%zu %zu is sleeping\n", timestamp_in_ms, philo->id);
	else if (status == THINKING)
		printf("%zu %zu is thinking\n", timestamp_in_ms, philo->id);
	pthread_mutex_unlock(&philo->data->mutex_print);
}
