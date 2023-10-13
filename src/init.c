#include "../philo.h"

t_philo	*initialize_individual(t_inf *info, int i)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (error("malloc()"), NULL);
	new->nom = 0;
	new->info = info;
	new->id = i + 1;
	new->last_meal = 0;
	if (!i)
	{
		new->right = info->forks + (info->arg[NOP] - 1);
		new->left = info->forks + i;
	}
	else
	{
		new->left = info->forks + i - 1;
		new->right = info->forks + i;
	}
	return (new);
}

bool	init_arg(t_inf *info, char **argv)
{
	info->arg = malloc(5 * sizeof(int));
	if (!info->arg)
		return (error("malloc()"), true);
	info->arg[NOP] = ft_atoi(argv[1]);
	info->arg[TTD] = ft_atoi(argv[2]);
	info->arg[TTE] = ft_atoi(argv[3]);
	info->arg[TTS] = ft_atoi(argv[4]);
	info->arg[NOM] = -1;
	if (argv[5])
	{
		info->arg[NOM] = ft_atoi(argv[5]);
		if (info->arg[NOM] == -1)
			return (free(info->arg), true);
	}
	if (info->arg[NOP] < 0 || info->arg[TTD] < 0 ||\
		info->arg[TTE] < 0 || info->arg[TTS] < 0)
		return (free(info->arg), true);
	return (false);
}

pthread_mutex_t	*create_mutexes(int amount)
{
	pthread_mutex_t	*new;
	int				i;

	new = malloc((amount) * sizeof(pthread_mutex_t));
	if (!new)
		return (error("malloc()"), NULL);
	i = 0;
	while (i < amount)
	{
		if (pthread_mutex_init(new + i, NULL))
		{
			error("pthread_mutex_init()");
			return (destroy_mutexes(new, i), NULL);
		}
		i++;
	}
	return (new);
}

bool	initialize_info(t_inf *info, char **argv)
{
	info->th = NULL;
	info->forks = NULL;
	info->last_meal = NULL;
	info->mutex = NULL;
	info->philosophers = NULL;
	info->sos = 0;
	info->nom = 0;
	info->end_of_simulation = false;
	info->start_ok = true;
	if (init_arg(info, argv))
		return (true);
	info->forks = create_mutexes(info->arg[NOP]);
	if (!info->forks)
		return (free_info(info), true);
	info->last_meal = create_mutexes(info->arg[NOP]);
	if (!info->last_meal)
		return (free_info(info), true);
	info->mutex = create_mutexes(MUTEXES);
	if (!info->mutex)
		return (free_info(info), true);
	info->th = malloc((info->arg[NOP]) * sizeof(pthread_t));
	if (!info->th)
		return (free_info(info), true);
	return (false);
}
