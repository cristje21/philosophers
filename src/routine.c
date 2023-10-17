#include "../philo.h"

static bool	nom_achieved(t_philo *p, t_inf *info, int nom)
{
	if (nom == -1)
		return (false);
	p->nom++;
	if (p->nom == nom)
	{
		p->nom = 0;
		un_lock_mutex(info->mutex + MEALS, info->mutex + END, 0);
		info->nom++;
		if (info->nom == info->arg[NOP])
			info->end_of_simulation = true;
		un_lock_mutex(info->mutex + END, info->mutex + MEALS, 1);
		return (true);
	}
	return (false);
}

static bool	eat(t_philo *p)
{
	pthread_mutex_lock(p->right);
	if (print(p->info, p->id, "has taken a fork") || p->left == p->right)
		return (un_lock_mutex(p->right, NULL, 1), true);
	pthread_mutex_lock(p->left);
	if (print(p->info, p->id, "has taken a fork") ||\
		print(p->info, p->id, "is eating"))
		return (un_lock_mutex(p->right, p->left, 1), true);
	pthread_mutex_lock(p->info->mutex + MEALS);
	p->last_meal = gettime();
	pthread_mutex_unlock(p->info->mutex + MEALS);
	if (nom_achieved(p, p->info, p->info->arg[NOM]) || eos(p->info) ||\
		msleep(p->info->arg[TTE], p->info))
		return (un_lock_mutex(p->right, p->left, 1), true);
	return (un_lock_mutex(p->right, p->left, 1), false);
}

static bool	p_sleep(t_philo *philo)
{
	if (print(philo->info, philo->id, "is sleeping") || eos(philo->info) ||\
		msleep(philo->info->arg[TTS], philo->info))
		return (true);
	return (false);
}

bool	think(t_philo *philo)
{
	if (print(philo->info, philo->id, "is thinking"))
		return (true);
	return (false);
}

void	*routine(void *philo)
{
	if (!start_ok(philo))
		return (NULL);
	while (1)
	{
		if (eat(philo))
			break ;
		if (p_sleep(philo))
			break ;
		if (think(philo))
			break ;
	}
	return (NULL);
}
