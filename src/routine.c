/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvan-sch <cvan-sch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:25:11 by cvan-sch          #+#    #+#             */
/*   Updated: 2023/10/30 14:27:40 by cvan-sch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	nom_achieved(t_philo *p, t_inf *info, int nom)
{
	if (nom == -1)
		return (false);
	p->nom++;
	if (p->nom == nom)
	{
		p->nom = 0;
		pthread_mutex_lock(info->mutex + MEALS);
		pthread_mutex_lock(info->mutex + END);
		info->nom++;
		if (info->nom == info->arg[NOP])
			info->end_of_simulation = true;
		pthread_mutex_unlock(info->mutex + END);
		pthread_mutex_unlock(info->mutex + MEALS);
		return (true);
	}
	return (false);
}

int	take_fork(pthread_mutex_t *fork, int id, t_inf *info)
{
	pthread_mutex_lock(fork);
	return (print(info, id, "has taken a fork"));
}

static bool	eat(t_philo *p)
{
	bool ret;

	ret = false;
	if (p->right == p->left)
		return (true);
	if (take_fork(p->right, p->id, p->info))
	{
		pthread_mutex_unlock(p->right);
		return (true);
	}
	if (take_fork(p->left, p->id, p->info))
		ret = true;
	if (!print(p->info, p->id, "is eating"))
	{
		pthread_mutex_lock(p->info->mutex + MEALS);
		p->last_meal = gettime();
		pthread_mutex_unlock(p->info->mutex + MEALS);
		if (nom_achieved(p, p->info, p->info->arg[NOM]) || \
			eos(p->info) || \
			msleep(p->info->arg[TTE], p->info))
			ret = true;
	}
	pthread_mutex_unlock(p->right);
	pthread_mutex_unlock(p->left);
	return (ret);
}

static bool	p_sleep(t_philo *philo)
{
	if (print(philo->info, philo->id, "is sleeping") || \
		msleep(philo->info->arg[TTS], philo->info))
		return (true);
	return (false);
}

bool	think(t_philo *philo)
{
	return (print(philo->info, philo->id, "is thinking"));
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
