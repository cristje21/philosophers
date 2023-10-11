#include "../philo.h"

bool	start_ok(t_philo *philo)
{
	bool	ret;

	un_lock_mutex(philo->info->mutex + START, philo->info->mutex + END, 0);
	if (philo->info->start_ok != true)
		ret = false;
	else
	{
		philo->last_meal = philo->info->sos;
		ret = true;
	}
	un_lock_mutex(philo->info->mutex + START, philo->info->mutex + END, 1);
	return (ret);
}

static bool	check_validity(char *s)
{
	int	i;
	int	preceding_zeros;

	i = 0;
	if (s[i] == '-')
		return (error("only positive numbers make sense"), false);
	while (s[i] == '0')
		i++;
	preceding_zeros = i;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (error("some characters are not numbers"), false);
		else if (i > 9 + preceding_zeros)
			return (error("one or more arguments are bigger than an integer"), false);
		i++;
	}
	return (true);
}

int	ft_atoi(char *s)
{
	long	result;

	result = 0;
	if (!s || !check_validity(s))
		return (-1);
	while ((*s >= '\t' && *s <= '\r') || *s == ' ')
		s++;
	while (*s >= '0' && *s <= '9')
		result = result * 10 + *(s++) - '0';
	if (result > 2147483647)
		return (-1);
	return (result);
}

bool	print(t_inf *info, int id, char *action)
{
	bool	end;

	end = false;
	pthread_mutex_lock(info->mutex + END);
	if (info->end_of_simulation == false)
		printf("%lu %d %s\n", gettime() - info->sos, id, action);
	else
		end = true;
	pthread_mutex_unlock(info->mutex + END);
	return (end);
}

void	un_lock_mutex(pthread_mutex_t *l1, pthread_mutex_t *l2, bool action)
{
	if (action == 0)
	{
		pthread_mutex_lock(l1);
		if (l2)
			pthread_mutex_lock(l2);
	}
	else
	{
		pthread_mutex_unlock(l1);
		if (l2)
			pthread_mutex_unlock(l2);
	}
}
