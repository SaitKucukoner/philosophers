#include "philo.h"

int argument_control(int argc, char **argv)
{
    int i;
    int j;

    if (argc != 5 && argc != 6)
        return (1);
    i = 1;
    while (i < argc)
    {
        j = 0;
        while (argv[i][j] && (argv[i][j] == ' ' || argv[i][j] == '\t'))
            j++;
        if (argv[i][j] == '+')
            j++;
        if (!argv[i][j] || argv[i][j] < '0' || argv[i][j] > '9')
            return (2);
        while (argv[i][j] && ('0' <= argv[i][j]) && argv[i][j] <= '9')
            j++;
        if (argv[i][j])
            return (2);
        i++;
    }
    return (0);
}

void    create_threads_and_start(t_data *data)
{
    pthread_t   observer;
    size_t      i;

    i = 0;
    pthread_mutex_lock(&data->mutex_thread_start);
    data->time_of_sim_start = get_time_ms();
    while (i < data->number_of_philosophers)
    {
        data->philos[i].time_of_last_eaten_meal = data->time_of_sim_start;
        pthread_create(&data->philos[i].thread, NULL, philosopher_life, &data->philos[i]);
        i++;
    }
    data->threads_ready_to_start = 1;
    pthread_mutex_unlock(&data->mutex_thread_start);
    pthread_create(&observer, NULL, observer_process, data);
    i = 0;
    while (i < data->number_of_philosophers)
    {
        pthread_join(data->philos[i].thread, NULL);
        i++;
    }
    pthread_join(observer, NULL);
}

void    free_and_destroy(t_data *data)
{
    size_t  i;

    i = 0;
    while (i < data->number_of_philosophers)
    {
        pthread_mutex_destroy(&data->mutex_fork[i]);
        pthread_mutex_destroy(&data->philos[i].mutex_meal);
        i++;
    }
    free(data->mutex_fork);
    free(data->philos);
    pthread_mutex_destroy(&data->mutex_print);
    pthread_mutex_destroy(&data->mutex_sim_end);
    pthread_mutex_destroy(&data->mutex_thread_start);
}

int main(int argc, char **argv)
{
    t_data  data;
    int     arg_control;

    arg_control = argument_control(argc, argv);
    if (arg_control == 1 || arg_control == 2)
    {
        if (arg_control == 1)
            write(2, "Error: wrong argument count\n", 28);
        else
            write(2, "Error: wrong argument type\n", 27);
        return (1);
    }
    if (init_data(&data, argc, argv))
        return (1);
    if (init_forks(&data))
        return (1);
    if (init_philosophers(&data))
        return (1);
    create_threads_and_start(&data);
    free_and_destroy(&data);
    return (0);
}
