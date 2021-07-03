/*
* Created: 2021/03/24
*/

#include "../header/philo_two.h"

static void	ft_printf_str2(int n)
{
	if (n == -1)
		ft_putstr_fd("Bad arguments\n", 2);
	else if (n == -2)
		ft_putstr_fd("Problem in malloc\n", 2);
	else if (n == -3)
		ft_putstr_fd("Problem in pthread_create\n", 2);
	else if (n == -4)
		ft_putstr_fd("Problem in semaphore\n", 2);
}

int			ft_printf_str(int n)
{
	if (n == -1 || n == -2 || n == -3 || n == -4)
		ft_printf_str2(n);
	else if (n == 0)
		ft_putstr_fd("is eating\n", 1);
	else if (n == 1)
		ft_putstr_fd("is sleeping\n", 1);
	else if (n == 2)
		ft_putstr_fd("has taken a fork\n", 1);
	else if (n == 3)
		ft_putstr_fd("is thinking\n", 1);
	else if (n == 666)
	{
		ft_putstr_fd("All philosophers ate ", 1);
		return ('Z');
	}
	else
	{
		ft_putstr_fd("died\n", 1);
		return ('Z');
	}
	return ('z');
}

static void	ft_display_message2(t_two *philo, int type, int n)
{
	char	*str;

	str = NULL;
	if (type != 666 && n == 1)
	{
		ft_putnbr_fd(philo->position + 1, 1);
		ft_putstr_fd("\t", 1);
	}
	else if (type == 666 && n == 2)
	{
		str = ft_itoa(philo->info->opt.must_eat_count, 10, 0, str);
		ft_putstr_fd(str, 1);
		free(str);
		ft_putstr_fd(" times!\n", 1);
	}
}

static char	ft_cercl_dis_messg(t_two *philo, int type, char z, size_t n)
{
	ft_putnbr_fd(n, 1);
	ft_putstr_fd("\t", 1);
	if (type != 666)
		ft_display_message2(philo, type, 1);
	z = ft_printf_str(type);
	if (type == 666)
		ft_display_message2(philo, type, 2);
	return (z);
}

int			ft_display_message(t_two *philo, int type, int ind, size_t n)
{
	static char z = 'z';

	if (sem_wait(philo->info->write_m) != 0)
		return (1);
	if (z == 'z')
	{
		if (type == 4)
		{
			gettimeofday(&philo->tv, NULL);
			n = philo->tv.tv_sec * (size_t)1000 + philo->tv.tv_usec / \
				1000 - philo->info->start;
		}
		else
			n = philo->info->p_two->print_time;
		z = ft_cercl_dis_messg(philo, type, z, n);
		ind = 0;
	}
	if (sem_post(philo->info->write_m))
		return (1);
	return (ind);
}
