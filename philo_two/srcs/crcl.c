/*
* Created: 2021/03/24
*/

#include "../header/philo_two.h"

void	ft_correct_time2(t_two *philo, int n, size_t *s1, size_t *s2)
{
	if (n == 1)
	{
		if (*s1 < philo->info->p_two->print_time || \
			*s2 < philo->info->p_two->print_time)
		{
			if (*s1 < *s2)
				philo->info->p_two->print_time = *s1;
			else
				philo->info->p_two->print_time = *s2;
		}
	}
	else if (n == 3)
	{
		*s2 += philo->info->opt.time_to_eat;
		if (philo->info->p_two->print_time > *s2)
			philo->info->p_two->print_time = *s2;
		else
			*s1 = *s2;
	}
}

void	ft_correct_time(t_two *philo, int n)
{
	static size_t s_crrt1 = 0;
	static size_t s_crrt2 = 0;

	if (s_crrt1 == 0)
	{
		s_crrt1 = philo->info->p_two->print_time;
		s_crrt2 = s_crrt1;
	}
	if (n == 1)
		ft_correct_time2(philo, n, &s_crrt1, &s_crrt2);
	else if (n == 2)
	{
		s_crrt2 = philo->info->p_two->print_time;
		s_crrt1 = s_crrt2;
	}
	else if (n == 3)
		ft_correct_time2(philo, n, &s_crrt1, &s_crrt2);
	else if (n == 4)
	{
		s_crrt2 += philo->info->opt.time_to_sleep;
		if (philo->info->p_two->print_time > s_crrt2)
			philo->info->p_two->print_time = s_crrt2;
		else
			s_crrt1 = s_crrt2;
	}
}

void	ft_time2(t_two *philo, int n)
{
	if (n == 2)
	{
		philo->is_eating = 1;
		ft_timer(philo);
		ft_correct_time(philo, 2);
		philo->limit = philo->info->p_two->print_time + \
			philo->info->opt.time_to_die + philo->lll;
		ft_display_message(philo, 0, 1, 0);
	}
	else if (n == 3)
	{
		ft_timer(philo);
		ft_correct_time(philo, 3);
		ft_display_message(philo, 1, 1, 0);
	}
}

int		ft_time(t_two *philo, int n)
{
	sem_wait(philo->info->for_time);
	if (n == 1)
	{
		ft_timer(philo);
		ft_correct_time(philo, 1);
		ft_display_message(philo, 2, 1, 0);
	}
	else if (n == 2 || n == 3)
		ft_time2(philo, n);
	else if (n == 4)
	{
		ft_timer(philo);
		ft_correct_time(philo, 4);
		ft_display_message(philo, 3, 1, 0);
	}
	sem_post(philo->info->for_time);
	return (0);
}

int		ft_cycle_r(t_two *philo)
{
	sem_wait(philo->info->forks_m);
	ft_time(philo, 1);
	sem_wait(philo->info->forks_m);
	ft_time(philo, 1);
	ft_time(philo, 2);
	usleep(philo->info->opt.time_to_eat * 1000);
	sem_post(philo->eat_count_m);
	ft_time(philo, 3);
	philo->is_eating = 0;
	sem_post(philo->info->forks_m);
	sem_post(philo->info->forks_m);
	usleep(philo->info->opt.time_to_sleep * 1000);
	ft_time(philo, 4);
	return (0);
}
