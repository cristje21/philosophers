#include "../philo.h"

int	main(int argc, char *argv[])
{
	t_inf	info;

	if (argc < 5 || argc > 6)
		return (error("philo: usage"), 1);
	if (initialize_info(&info, argv))
		return (1);
	if (simulation(&info))
		return (1);
}
