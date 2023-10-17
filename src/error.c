#include	"../philo.h"

void	destroy_mutexes(pthread_mutex_t *arr, int amount)
{
	if (!arr)
		return ;
	amount -= 1;
	while (amount >= 0)
	{
		if (pthread_mutex_destroy(&arr[amount]))
			error("pthread_mutex_destroy()");
		amount--;
	}
	free(arr);
}

void	free_philo(t_philo **philosophers, int amount)
{
	if (!philosophers)
		return ;
	while (--amount >= 0)
		free(philosophers[amount]);
	free(philosophers);
}

void	free_info(t_inf *info)
{
	free_philo(info->philosophers, info->arg[NOP]);
	destroy_mutexes(info->forks, info->arg[NOP]);
	destroy_mutexes(info->mutex, MUTEXES);
	free(info->th);
	free(info->arg);
}

void	error(char *msg)
{
	int	i;

	i = 0;
	while (*(msg + i))
		i++;
	write(2, "philo: ", 7);
	write(2, msg, i);
	write(2, "\n", 1);
}

bool	eos(t_inf *info)
{
	bool	end;

	end = false;
	pthread_mutex_lock(info->mutex + END);
	if (info->end_of_simulation)
		end = true;
	pthread_mutex_unlock(info->mutex + END);
	return (end);

}