/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvan-sch <cvan-sch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:25:17 by cvan-sch          #+#    #+#             */
/*   Updated: 2023/10/30 14:28:13 by cvan-sch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	start_ok(t_philo *p)
{
	bool	ret;

	pthread_mutex_lock(p->info->mutex + MEALS);
	if (p->info->start_ok != true)
		ret = false;
	else
	{
		p->last_meal = p->info->sos;
		ret = true;
	}
	pthread_mutex_unlock(p->info->mutex + MEALS);
	if (!(p->id % 2))
	{
		think(p);
		msleep(p->info->arg[TTE] / 2, p->info);
	}
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
			return (error("one or more arguments are bigger than an integer") \
			, false);
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
