#include "philosophers.h"

static long	supervisor_checks_meal(long time_start_meal, t_philo *supervisor_data)
{
	pthread_mutex_lock(supervisor_data->supervisor_lock);
	if (supervisor_data->new_meal_flag == 1)
	{
		time_start_meal = get_time();
		supervisor_data->new_meal_flag = 0;
	}
	pthread_mutex_unlock(supervisor_data->supervisor_lock);
	return (time_start_meal);
}

/* supervisor routine
 * 		check every 10ms if (time_since_last_meal > time_to_die)
 * 		keeps adding time to var
 * 		if true
 * 			print death, set up flag, exit
 */

static int	supervisor_checks_thread_state(t_philo *supervisor_data)
{
	int	thread_state;

	pthread_mutex_lock(supervisor_data->supervisor_lock);
	pthread_mutex_lock(supervisor_data->common->alive_lock);
	thread_state = (supervisor_data->thread_ended_flag || !supervisor_data->common->alive_flag);
	pthread_mutex_unlock(supervisor_data->supervisor_lock);
	pthread_mutex_unlock(supervisor_data->common->alive_lock);
	return (thread_state);
}

void	*supervisor_routine(void *routine_args)
{
	t_philo		*supervisor_data;
	long		time_start_meal;
	long		time_start;
	long		time_since_last_meal;

	supervisor_data = (t_philo *)routine_args;
	time_start = get_time();
	time_start_meal = time_start;
	while (1)
	{
		/*if (!supervisor_data->common->everyone_alive_flag)
			return (NULL);
		 check if philo finished his meals */
		if (supervisor_checks_thread_state(supervisor_data))
			return (NULL);
		time_start_meal = supervisor_checks_meal(time_start_meal, supervisor_data);
		time_since_last_meal = get_time() - time_start_meal;
		//printf("\tsup:|%d|%ld\n", supervisor_data->id, time_since_last_meal);
		if (time_since_last_meal > supervisor_data->common->time_to_die)
		{
			if (supervisor_checks_thread_state(supervisor_data))
				return (NULL);
			print_status(DEAD_ID, get_time() - time_start, supervisor_data->id);
			pthread_mutex_lock(supervisor_data->common->alive_lock);
			supervisor_data->common->alive_flag = 0;
			pthread_mutex_unlock(supervisor_data->common->alive_lock);
			return (NULL);
		}
		//usleep(10 * 1000);
	}
	return (NULL);
}