#include "../philo.h"

bool	init_arg(t_inf *info, char **argv)
{
	info->arg = malloc(5 * sizeof(int));
	if (!info->arg)
		return (error("philo: malloc()"), true);
	info->arg[NOP] = ft_atoi(argv[1]);
	info->arg[TTD] = ft_atoi(argv[2]);
	info->arg[TTE] = ft_atoi(argv[3]);
	info->arg[TTS] = ft_atoi(argv[4]);
	info->arg[NOM] = -1;
	if (argv[5])
		info->arg[NOM] = ft_atoi(argv[5]);
	if (info->arg[NOP] < 0 || info->arg[TTD] < 0 ||\
		info->arg[TTE] < 0 || info->arg[TTS] < 0)
		return (free(info->arg), true);
	return (false);
}

pthread_mutex_t	*create_mutexes(int amount)
{
	pthread_mutex_t	*new;
	int				i;

	new = malloc((amount + 1) * sizeof(pthread_mutex_t));
	if (!new)
		return (error("philo: malloc()"), NULL);
	i = 0;
	while (i < amount)
	{
		if (pthread_mutex_init(&new[i], NULL))
		{
			destroy_mutexes(new, i - 1);
			return (error("philo: malloc()"), NULL);
		}
		i++;
	}
	return (new);
}

bool	initialize_info(t_inf *info, char **argv)
{
	if (init_arg(info, argv))
		return (true);
	info->nom = 0;
	info->isdead = 0;
	info->forks = create_mutexes(info->arg[NOP]);
	if (!info->forks)
		return (free(info->arg), true);
	info->mutex = create_mutexes(3);
	if (!info->mutex)
	{
		destroy_mutexes(info->forks, info->arg[NOP]);
		return (free(info->arg), true);
	}
	info->philos = malloc((info->arg[NOP] + 1) * sizeof(pthread_t));
	if (!info->philos)
	{
		destroy_mutexes(info->forks, info->arg[NOP]);
		destroy_mutexes(info->mutex, 3);
		return (free(info->arg), error("philo: malloc()"), true);
	}
	return (false);
}
