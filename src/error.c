#include	"../philo.h"

void	destroy_mutexes(pthread_mutex_t *arr, int i)
{
	while (i >= 0)
	{
		if (pthread_mutex_destroy(&arr[i]))
			error("philo: failed to destroy mutex");
		i--;
	}
}

void	error(char *msg)
{
	printf("%s\n", msg);
}
