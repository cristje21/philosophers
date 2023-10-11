#include "../philo.h"

static bool	nom_achieved(t_philo *p, t_inf *info, int nom)
{
	if (nom == -1)
		return (false);
	p->nom++;
	if (p->nom == nom)
	{
		un_lock_mutex(info->mutex + MNOM, info->mutex + END, 0);
		info->nom++;
		if (info->nom == info->arg[NOP])
			info->end_of_simulation = true;
		un_lock_mutex(info->mutex + MNOM, info->mutex + END, 1);
		return (true);
	}
	return (false);
}

static bool	eat(t_philo *p)
{
	pthread_mutex_lock(p->left);
	if (print(p->info, p->id, "has taken a fork") || p->left == p->right)
		return (un_lock_mutex(p->left, NULL, 1), true);
	pthread_mutex_lock(p->right);
	if (print(p->info, p->id, "has taken a fork") ||\
		print(p->info, p->id, "is eating"))
		return (un_lock_mutex(p->left, p->right, 1), true);
	pthread_mutex_lock(p->info->last_meal + (p->id - 1));
	p->last_meal = gettime();
	pthread_mutex_unlock(p->info->last_meal + (p->id - 1));
	if (nom_achieved(p, p->info, p->info->arg[NOM]) || eos(p->info) ||\
		msleep(p->info->arg[TTE], p->info))
		return (un_lock_mutex(p->left, p->right, 1), true);
	return (un_lock_mutex(p->left, p->right, 1), false);
}

static bool	p_sleep(t_philo *philo)
{
	if (print(philo->info, philo->id, "is sleeping") ||\
		msleep(philo->info->arg[TTS], philo->info))
		return (true);
	return (false);
}

static bool	think(t_philo *philo)
{
	if (print(philo->info, philo->id, "is thinking"))
		return (true);
	if (!(philo->id % 2) && !philo->nom)
	{
		if (msleep(1, philo->info))
			return (true);
	}
	return (false);
}

void	*routine(void *philo)
{
	if (!start_ok(philo))
		return (NULL);
	while (1)
	{
		if (think(philo))
			break ;
		if (eat(philo))
			break ;
		if (p_sleep(philo))
			break ;
	}
	return (NULL);
}
