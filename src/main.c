/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvan-sch <cvan-sch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:25:08 by cvan-sch          #+#    #+#             */
/*   Updated: 2023/10/30 14:27:17 by cvan-sch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	join_philosophers(t_inf *info, int i)
{
	bool	ret;

	ret = false;
	while (i >= 0)
	{
		if (pthread_join(info->th[i], NULL))
		{
			error("pthread_join()");
			ret = true;
		}
		i--;
	}
	return (ret);
}

static int	dinner_time(t_inf *info, int i)
{
	int	j;

	j = i - 1;
	if (!info->arg[NOP] || !info->arg[NOM] || i != info->arg[NOP])
		info->start_ok = false;
	else
		info->sos = gettime();
	return (j);
}

static void	monitoring(t_inf *info, t_philo **philosophers)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < info->arg[NOP])
		{
			if (eos(info))
				return ;
			pthread_mutex_lock(info->mutex + MEALS);
			if (info->sos && philosophers[i]->last_meal && \
				gettime() - philosophers[i]->last_meal \
				>= ((unsigned long)info->arg[TTD]))
			{
				pthread_mutex_unlock(info->mutex + MEALS);
				pthread_mutex_lock(info->mutex + END);
				printf("%lu %d died\n", gettime() - info->sos, i + 1);
				info->end_of_simulation = true;
				pthread_mutex_unlock(info->mutex + END);
				return ;
			}
			pthread_mutex_unlock(info->mutex + MEALS);
			usleep(100);
			i++;
		}
	}
}

static int	let_there_be_philosophers(t_inf *info)
{
	int		i;

	i = 0;
	info->philosophers = malloc(info->arg[NOP] * sizeof(t_philo *));
	if (!info->philosophers)
		return (true);
	pthread_mutex_lock(info->mutex + MEALS);
	while (i < info->arg[NOP])
	{
		info->philosophers[i] = initialize_individual(info, i);
		if (!info->philosophers[i])
			break ;
		if (pthread_create(&info->th[i], NULL, &routine, info->philosophers[i]))
		{
			error("pthread_create()");
			free(info->philosophers[i]);
			break ;
		}
		i++;
	}
	i = dinner_time(info, i);
	pthread_mutex_unlock(info->mutex + MEALS);
	return (i);
}

int	main(int argc, char *argv[])
{
	t_inf	info;
	int		i;
	int		ret;

	ret = 0;
	if (argc < 5 || argc > 6)
		return (error("ask Cris for further instructions"), 1);
	if (initialize_info(&info, argv))
		return (1);
	i = let_there_be_philosophers(&info);
	if (i == info.arg[NOP] - 1 && info.start_ok)
		monitoring(&info, info.philosophers);
	else
		ret++;
	if (join_philosophers(&info, i))
		ret++;
	free_info(&info);
	return (ret);
}
