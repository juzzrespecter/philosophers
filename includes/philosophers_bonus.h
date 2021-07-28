#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H
# include <sys/time.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <unistd.h>
# include <semaphore.h>
# include <signal.h>

# define THINK_ID 0
# define FORK_ID 1
# define EAT_ID 2
# define SLEEP_ID 3
# define DEAD_ID 4
# define FINISH_ID 5

# define PHILO_DEAD 0 

typedef struct s_data
{
	pthread_t		*pthread_arr;
	sem_t			*fork_pile;
	char			*sem_name;
	unsigned int	n_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				times_must_eat;
	sem_t			*supervisor_lock;
	int				meal_flag;
	int			id;
}	t_data;

unsigned int	ft_atou(char *a);
int				ft_isdigit(int c);

long			get_time(void);
int				philo_err_mgmt(int argc, char **argv);
void			philo_routine(int id, t_data *data);
void			print_status(int status_id, long time, int philo_id);

#endif
