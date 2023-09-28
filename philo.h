#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

# include <sys/time.h>

# include <stdbool.h>

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

enum	e_arguments
{
	NOP,
	TTD,
	TTE,
	TTS,
	NOM,
};

enum	e_mutex
{
	DEATHS,
	MEALS,
	PRINT,
};

typedef struct		s_inf
{
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*mutex;
	unsigned long	sos;
	bool			isdead;
	int				nom;
	int				*arg;
}					t_inf;

typedef struct		s_philo
{
	t_inf			info;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	unsigned long	last_meal;
	int				id;
}					t_philo;

void	error(char *msg);
int		ft_atoi(char *s);
void	destroy_mutexes(pthread_mutex_t *arr, int i);

#endif