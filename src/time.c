#include "../philo.h"

unsigned long	gettime(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (error("gettimeofday()"), 0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

bool	msleep(unsigned long mseconds, t_inf *info)
{
	unsigned long	time;

	time = gettime();
	while (gettime() - time < mseconds)
	{
		usleep(mseconds / 10);
		if (eos(info))
			break ;
	}
	return (false);
}
