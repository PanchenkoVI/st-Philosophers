/*
* Created: 2021/03/24
*/

#include "../header/philo_one.h"

int		ft_timer(t_one *philo)
{
	gettimeofday(&philo->tv, NULL);
	if ((philo->tv.tv_sec * (size_t)1000) + \
		(philo->tv.tv_usec / 1000) > philo->limit)
	{
		ft_display_message(philo, 4);
		return (1);
	}
	return (0);
}

void	ft_cycle_clear(t_info *info, int i, int n)
{
	while (i < info->opt.amount)
	{
		if (n == 0)
			pthread_mutex_destroy(&info->forks_m[i]);
		else
			pthread_mutex_destroy(&info->p_one[i].eat_m);
		i++;
	}
}

void	ft_clear_struct(t_info *info, int i)
{
	pthread_mutex_destroy(&info->somebody_dead_m);
	pthread_mutex_destroy(&info->write_m);
	pthread_mutex_destroy(&info->write_tm);
	if (info->forks_m)
		ft_cycle_clear(info, i, 0);
	if (info->p_one)
		ft_cycle_clear(info, i, 1);
}
