/*
* Created: 2021/03/24
*/

#include "../header/philo_two.h"

static void	ft_monitor2(t_two *philo, size_t *i)
{
	gettimeofday(&philo->tv, NULL);
	if (*i == 20)
	{
		philo->lll = (philo->tv.tv_sec * (size_t)1000) + \
			(philo->tv.tv_usec / 1000) + philo->info->opt.time_to_eat / 2;
		*i = -1;
	}
	else
		philo->lll = (philo->tv.tv_sec * (size_t)1000) + \
			(philo->tv.tv_usec / 1000);
}

static void	*ft_monitor(void *philo_v)
{
	t_two		*philo;
	size_t		i;

	philo = (t_two*)philo_v;
	i = philo->info->opt.time_to_die - philo->info->opt.time_to_eat - \
		philo->info->opt.time_to_sleep;
	if (i >= 0 && i < 10)
		i = 20;
	while (1)
	{
		ft_monitor2(philo, &i);
		if (!philo->is_eating && (philo->tv.tv_sec * (size_t)1000) + \
			(philo->tv.tv_usec / 1000) > philo->limit)
		{
			if (ft_display_message(philo, 4, 1, 0))
				return ((void*)0);
			if (sem_post(philo->info->somebody_dead_m))
				return ((void*)0);
			return ((void*)0);
		}
		usleep(100);
	}
	return ((void*)0);
}

void		ft_timer(t_two *philo)
{
	static size_t str_time = 0;
	static size_t fsh_time = 0;

	if (str_time == 0)
	{
		gettimeofday(&philo->info->p_two->tv, NULL);
		str_time = philo->info->p_two->tv.tv_sec * (size_t)1000 + \
			philo->info->p_two->tv.tv_usec / 1000 - philo->info->start;
		if (str_time % 10 != 0)
			str_time = str_time - (str_time % 10);
		fsh_time = str_time;
	}
	gettimeofday(&philo->info->p_two->tv, NULL);
	str_time = philo->info->p_two->tv.tv_sec * (size_t)1000 + \
		philo->info->p_two->tv.tv_usec / 1000 - philo->info->start;
	if (str_time % 10 != 0)
		str_time = str_time - (str_time % 10);
	if (str_time == fsh_time)
		philo->info->p_two->print_time = fsh_time;
	else if (str_time > fsh_time)
	{
		philo->info->p_two->print_time = str_time;
		fsh_time = str_time;
	}
}

static void	*ft_routine(void *philo_v)
{
	t_two		*philo;
	int			i;

	i = 0;
	philo = (t_two*)philo_v;
	gettimeofday(&philo->tv, NULL);
	philo->last_eat = philo->tv.tv_sec * (size_t)1000 + \
		philo->tv.tv_usec / 1000;
	philo->lll = philo->last_eat;
	philo->limit = philo->last_eat + philo->info->opt.time_to_die;
	if (pthread_create(&philo->info->tid, NULL, &ft_monitor, philo_v) != 0)
		return ((void*)1);
	pthread_detach(philo->info->tid);
	while (1)
	{
		if (i == philo->info->opt.stop_eat)
			return ((void*)0);
		i++;
		if (ft_cycle_r(philo))
			return ((void*)0);
	}
}

int			ft_start_threads(t_info *info, int i)
{
	gettimeofday(&info->p_two->tv, NULL);
	info->start = (info->p_two->tv.tv_sec * (size_t)1000) +\
		(info->p_two->tv.tv_usec / 1000);
	if (info->opt.must_eat_count > 0)
	{
		if (pthread_create(&info->tid, NULL, \
			&ft_monitor_count, (void*)info) != 0)
			return (1);
		pthread_detach(info->tid);
	}
	while (i < info->opt.amount)
	{
		if (pthread_create(&info->tid, NULL, \
			&ft_routine, (void*)(&info->p_two[i])) != 0)
			return (1);
		pthread_detach(info->tid);
		usleep(100);
		i++;
	}
	return (0);
}
