/*
* Created: 2021/03/24
*/

#include "../header/philo_one.h"

static int		ft_new_j(t_one *philo, int j)
{
	if (j == philo->info->opt.amount)
	{
		if (j % 2 == 1)
			j = -1;
		else
			j = -2;
	}
	else if (j == philo->info->opt.amount - 1)
	{
		if (j % 2 == 1)
			j = -2;
		else
			j = -1;
	}
	return (j);
}

static int		ft_cycle_time(t_one *philo, int j, int *i)
{
	if (philo->position % 2 == 1)
	{
		while (j == -1)
		{
			if (ft_timer(philo) > 0)
				return (1);
		}
	}
	if (philo->position % 2 == 0 && *i != -1)
	{
		while (j == -2)
		{
			if (ft_timer(philo) > 0)
				return (1);
		}
	}
	return (0);
}

int				ft_eat_and_sleep(t_one *philo)
{
	pthread_mutex_lock(&philo->info->forks_m[philo->lfork]);
	ft_time(philo, 2);
	pthread_mutex_lock(&philo->info->forks_m[philo->rfork]);
	ft_time(philo, 2);
	gettimeofday(&philo->tv, NULL);
	philo->limit = philo->tv.tv_sec * (size_t)1000 + philo->tv.tv_usec / \
		1000 + philo->info->opt.time_to_die;
	ft_time(philo, 0);
	if (ft_timer(philo))
		return (1);
	usleep(philo->info->opt.time_to_eat * 900);
	if (ft_timer(philo))
		return (1);
	pthread_mutex_unlock(&philo->eat_m);
	if (ft_timer(philo))
		return (1);
	ft_time(philo, 1);
	pthread_mutex_unlock(&philo->info->forks_m[philo->lfork]);
	pthread_mutex_unlock(&philo->info->forks_m[philo->rfork]);
	return (0);
}

int				ft_cycle_r(t_one *philo)
{
	static int	i = -1;
	static int	j = 1;

	if (ft_cycle_time(philo, j, &i) == 1)
		return (1);
	if (ft_timer(philo) > 0)
		return (1);
	i = 1;
	if (j == -1 || j == -2)
		j = 0;
	j++;
	if (ft_timer(philo))
		return (1);
	if (ft_eat_and_sleep(philo) == 1)
		return (1);
	i = 0;
	j = ft_new_j(philo, j);
	usleep(philo->info->opt.time_to_sleep * 900);
	ft_time(philo, 3);
	if (ft_timer(philo))
		return (1);
	if (ft_timer(philo))
		return (1);
	return (0);
}
