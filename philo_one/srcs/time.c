/*
* Created: 2021/03/24
*/

#include "../header/philo_one.h"

int		ft_time2(t_one *philo, int i, size_t n)
{
	if (i == 1)
	{
		philo->last_action = philo->last_action + philo->info->opt.time_to_eat;
		if (philo->last_action > n)
			n = philo->last_action;
		else
			philo->last_action = n;
		philo->st = n;
		ft_display_message(philo, 1);
	}
	else if (i == 2)
	{
		philo->last_action = n;
		ft_display_message(philo, 2);
	}
	else if (i == 3)
	{
		philo->last_action = philo->st + philo->info->opt.time_to_sleep;
		ft_display_message(philo, 3);
	}
	return (n);
}

int		ft_time(t_one *philo, int i)
{
	static size_t n = 0;

	pthread_mutex_lock(&philo->info->write_tm);
	if (n == 0)
	{
		gettimeofday(&philo->tv, NULL);
		n = philo->tv.tv_sec * (size_t)1000 + philo->tv.tv_usec / \
			1000 - philo->info->start;
	}
	if (i == 0)
	{
		if (n < philo->last_action)
			philo->last_action = philo->limit - philo->info->opt.time_to_die - \
				philo->info->start;
		n = philo->last_action;
		ft_display_message(philo, 0);
	}
	else if (i == 1 || i == 2 || i == 3)
		n = ft_time2(philo, i, n);
	pthread_mutex_unlock(&philo->info->write_tm);
	return (0);
}
