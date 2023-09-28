#include "../philo.h"

static bool	check_validity(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-')
		return (error("philo: only positive numbers make sense"), false);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (error("philo: some characters are not numbers"), false);
		else if (i > 9)
			return (error("philo: one or more arguments are bigger than an integer"), false);
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
