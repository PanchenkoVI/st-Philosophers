/*
* Created: 2021/03/24
*/

#include "../header/philo_three.h"

int		ft_time(t_three *philo, int n)
{
	sem_wait(philo->info->for_time);
	if (n == 1)
		ft_display_message(philo, 2, 0);
	else if (n == 2)
	{
		philo->is_eating = 1;
		philo->limit = philo->print_time + philo->info->opt.time_to_die;
		ft_display_message(philo, 0, 0);
	}
	else if (n == 3)
	{
		philo->is_eating = 0;
		ft_display_message(philo, 1, 0);
	}
	else if (n == 4)
		ft_display_message(philo, 3, 0);
	sem_post(philo->info->for_time);
	return (0);
}

int		ft_cycle_r(t_three *philo)
{
	sem_wait(philo->info->forks_m);
	ft_time(philo, 1);
	sem_wait(philo->info->forks_m);
	ft_time(philo, 1);
	ft_time(philo, 2);
	usleep(philo->info->opt.time_to_eat * 1000);
	sem_post(philo->eat_count_m);
	ft_time(philo, 3);
	sem_post(philo->info->forks_m);
	sem_post(philo->info->forks_m);
	usleep(philo->info->opt.time_to_sleep * 1000);
	ft_time(philo, 4);
	return (0);
}
