#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define NOP
# define TTD
# define TTE
# define TTS
# define NOE

typedef struct s_inf
{
	int				*param;
	pthread_mutex_t	w_lock;
}					t_inf;


typedef struct	s_philo
{
	t_inf	*i;
	int		p_no;
}			t_philo;

#endif