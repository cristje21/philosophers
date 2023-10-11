#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <sys/types.h>

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct	s_philo	t_philo;

enum	e_arg
{
	NOP,
	TTD,
	TTE,
	TTS,
	NOM,
};

enum	e_time
{
	MS,
	US,
};

enum	e_mutex
{
	END,
	MNOM,
	START,
	MUTEXES,
};

typedef struct		s_inf
{
	pthread_t		*th;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*last_meal;
	pthread_mutex_t	*mutex;
	t_philo			**philosophers;
	unsigned long	sos;
	bool			end_of_simulation;
	bool			start_ok;
	int				nom;
	int				*arg;
}					t_inf;

typedef struct		s_philo
{
	t_inf			*info;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	unsigned long	last_meal;
	int				nom;
	int				id;
}					t_philo;

void			error(char *msg);
void			destroy_mutexes(pthread_mutex_t *arr, int i);
void			free_info(t_inf *info);
void			free_philo(t_philo **philosophers, int amount);
bool			eos(t_inf *info);

int				ft_atoi(char *s);
bool			start_ok(t_philo *philo);
void			un_lock_mutex(pthread_mutex_t *l1, pthread_mutex_t *l2, bool action);
bool			print(t_inf *info, int id, char *action);

t_philo			*initialize_individual(t_inf *info, int i);
bool			init_arg(t_inf *info, char **argv);
bool			initialize_info(t_inf *info, char **argv);
pthread_mutex_t	*create_mutexes(int amount);

void			*routine(void *philo);

unsigned long	gettime(void);
bool			msleep(unsigned long u_seconds, t_inf *info);

#endif