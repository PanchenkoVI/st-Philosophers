/*
* Created: 2021/03/24
*/

#include "../header/philo_three.h"

static void	*ft_monitor_count(void *inf)
{
	t_info	*state;
	int		total;
	int		i;

	state = (t_info*)inf;
	total = 0;
	while (total < state->opt.must_eat_count)
	{
		i = 0;
		while (i < state->opt.amount)
			sem_wait(state->p_three[i++].eat_count_m);
		total++;
	}
	ft_display_message(&state->p_three[0], 666, 0);
	sem_post(state->somebody_dead_m);
	return ((void*)0);
}

static void	*ft_monitor(void *trd_philo)
{
	t_three		*philo;

	philo = (t_three*)trd_philo;
	while (1)
	{
		gettimeofday(&philo->tv, NULL);
		philo->print_time = (philo->tv.tv_sec * \
			(size_t)1000) + (philo->tv.tv_usec / 1000);
		if (!philo->is_eating && (philo->tv.tv_sec * (size_t)1000) + \
			(philo->tv.tv_usec / 1000) - philo->lll > philo->limit)
		{
			ft_display_message(philo, 4, 0);
			sem_post(philo->info->somebody_dead_m);
			return ((void*)0);
		}
		usleep(100);
	}
	return ((void*)0);
}

static int	ft_routine(t_three *trd_philo)
{
	t_three		*philo;
	int			i;

	philo = (t_three*)trd_philo;
	gettimeofday(&philo->tv, NULL);
	philo->last_eat = philo->tv.tv_sec * \
		(size_t)1000 + philo->tv.tv_usec / 1000;
	philo->limit = philo->last_eat + philo->info->opt.time_to_die;
	philo->lll = 0;
	if (pthread_create(&philo->info->tid, NULL, &ft_monitor, philo) != 0)
		return (1);
	pthread_detach(philo->info->tid);
	i = 0;
	while (1)
	{
		if (i == philo->info->opt.stop_eat)
			return (0);
		i++;
		ft_cycle_r(philo);
		usleep(100);
	}
	return (0);
}

static int	ft_st_proc_crcl(t_info *info, int i)
{
	void	*philo;

	while (i < info->opt.amount)
	{
		philo = (void*)(&info->p_three[i]);
		info->p_three[i].pid = fork();
		if (info->p_three[i].pid < 0)
			return (1);
		else if (info->p_three[i].pid == 0)
		{
			ft_routine(&info->p_three[i]);
			exit(0);
		}
		usleep(200);
		i++;
	}
	return (0);
}

int			ft_start_process(t_info *info)
{
	if (info->opt.must_eat_count > 0)
	{
		if (pthread_create(&info->tid, NULL, \
			&ft_monitor_count, (void*)info) != 0)
			return (1);
		pthread_detach(info->tid);
	}
	gettimeofday(&info->p_three->tv, NULL);
	info->start = info->p_three->tv.tv_sec * (size_t)1000 + \
		info->p_three->tv.tv_usec / 1000;
	if (ft_st_proc_crcl(info, 0))
		return (1);
	return (0);
}
