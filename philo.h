#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef enum e_philo_status
{
    FORK,
    EATING,
    SLEEPING,
    THINKING,
    DIED
}   t_philo_status;

struct s_philo
{
    size_t          id;
    pthread_t       thread;
    size_t          number_of_eaten_meals;
    size_t          time_of_last_eaten_meal;
    pthread_mutex_t mutex_meal;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_data          *data;
};

struct s_data
{
    size_t          number_of_philosophers;
    size_t          time_to_die;
    size_t          time_to_eat;
    size_t          time_to_sleep;
    long            number_of_must_eat_each; 
    size_t          time_of_sim_start;
    int             is_sim_end;
    int             threads_ready_to_start;
    pthread_mutex_t mutex_thread_start;
    pthread_mutex_t mutex_sim_end;           
    pthread_mutex_t mutex_print;
    pthread_mutex_t *mutex_fork;
    t_philo         *philos;
};

size_t  ft_atoi(char *argument);
size_t  get_time_ms(void);
int     is_sim_end(t_data *data);
void    ft_usleep(size_t duration_ms, t_data *data);
void    print_philosopher_status(t_philo *philo, t_philo_status status);

int     init_data(t_data *data, int argc, char **argv);
int     init_forks(t_data *data);
int     init_philosophers(t_data *data);

int     take_up_the_forks(t_philo *philo);
void    put_down_the_forks(t_philo *philo);
int     eat(t_philo *philo);
void    sleep_and_think(t_philo *philo);

void    *philosopher_life(void *arg);
void    *observer_process(void *arg);


#endif