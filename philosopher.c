#include "philo.h"

int     is_philo_ready(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->mutex_thread_start);
    pthread_mutex_unlock(&philo->data->mutex_thread_start);
    if (!philo->data->threads_ready_to_start)
        return (1);
    return (0);
}

void    *philosopher_life(void *arg)
{
    t_philo *philo;

    philo = arg;
    if (is_philo_ready(philo))
        return (NULL);
    while (!is_sim_end(philo->data))
    {
        if (take_up_the_forks(philo))
            continue;
        if (eat(philo))
        {
            put_down_the_forks(philo);
            continue;
        }
        put_down_the_forks(philo);
        sleep_and_think(philo);
        if (philo->data->number_of_philosophers % 2 != 0)
            ft_usleep(philo->data->time_to_eat / 10, philo->data);
    }
    return (NULL);
}
