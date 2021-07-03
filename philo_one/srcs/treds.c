/*
* Created: 2021/03/24
*/

#include "../header/philo_one.h"

void	*ft_monitor_count(void *inf)
{
	t_info	*info;
	int		i;
	int		j;

	info = (t_info*)inf;
	j = 0;
	while (j < info->opt.must_eat_count)
	{
		i = 0;
		while (i < info->opt.amount)
		{
			pthread_mutex_lock(&info->p_one[i].eat_m);
			i++;
		}
		j++;
	}
	ft_display_message(&info->p_one[0], 666);
	pthread_mutex_unlock(&info->somebody_dead_m);
	return ((void*)0);
}

void	*ft_monitor(void *philo_v)
{
	t_one		*philo;

	philo = (t_one*)philo_v;
	while (1)
	{
		gettimeofday(&philo->tv, NULL);
		if (philo->info->p_one->is_eating == 0 && (philo->tv.tv_sec * \
			(size_t)1000) + (philo->tv.tv_usec / 1000) > philo->limit)
		{
			ft_display_message(philo, 4);
			pthread_mutex_unlock(&philo->info->somebody_dead_m);
			return ((void*)0);
		}
		usleep(100);
	}
}

void	*ft_routine(void *philo_v)
{
	t_one	*philo;
	int		i;

	i = 0;
	philo = (t_one*)philo_v;
	gettimeofday(&philo->tv, NULL);
	philo->limit = philo->tv.tv_sec * (size_t)1000 + \
		philo->tv.tv_usec / 1000 + philo->info->opt.time_to_die;
	philo->last_action = 0;
	if (pthread_create(&philo->info->tid, NULL, &ft_monitor, philo_v) != 0)
		return ((void*)-1);
	pthread_detach(philo->info->tid);
	while (1)
	{
		if (i == philo->info->opt.must_eat_count)
			break ;
		i++;
		if (ft_cycle_r(philo))
			break ;
		usleep(50);
	}
	return ((void*)0);
}

int		ft_threads(t_info *info, int i)
{
	gettimeofday(&info->p_one->tv, NULL);
	info->start = (info->p_one->tv.tv_sec * (size_t)1000) + \
		(info->p_one->tv.tv_usec / 1000);
	if (info->opt.must_eat_count > 0)
	{
		if (pthread_create(&info->tid, NULL, \
			&ft_monitor_count, (void*)info) != 0)
			return (1);
		pthread_detach(info->tid);
	}
	while (i < info->opt.amount)
	{
		if (pthread_create(&info->tid, NULL, &ft_routine, \
			(void*)(&info->p_one[i])) != 0)
			return (1);
		pthread_detach(info->tid);
		usleep(100);
		i++;
	}
	return (0);
}
