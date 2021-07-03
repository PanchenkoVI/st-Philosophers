/*
* Created: 2021/03/24
*/

#include "../header/philo_one.h"

static void		ft_printf_str2(int n)
{
	if (n == -1)
		ft_putstr_fd("Bad arguments\n", 2);
	else if (n == -2)
		ft_putstr_fd("Problem in malloc\n", 2);
	else if (n == -3)
		ft_putstr_fd("Problem in pthread_create\n", 2);
	else if (n == -4)
		ft_putstr_fd("Problem in mutex\n", 2);
	else if (n == 0)
		ft_putstr_fd("is eating\n", 1);
}

int				ft_printf_str(int n)
{
	if (n == -1 || n == -2 || n == -3 || n == -4 || n == 0)
		ft_printf_str2(n);
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
		return ('Y');
	}
	return ('z');
}

static void		ft_display_message2(t_one *philo, int type, int n)
{
	char		*str;

	if (type != 666 && n == 1)
	{
		ft_putnbr_fd(philo->position + 1, 1);
		ft_putstr_fd("\t", 1);
	}
	else if (type == 666 && n == 2)
	{
		str = NULL;
		str = ft_itoa(philo->info->opt.must_eat_count, 10, 0, str);
		ft_putstr_fd(str, 1);
		free(str);
		ft_putstr_fd(" times!\n", 1);
	}
}

int				ft_display_message(t_one *philo, int type)
{
	size_t		n;
	static char	z = 'z';

	pthread_mutex_lock(&philo->info->write_m);
	if (z == 'z')
	{
		if (type == 4)
			n = philo->limit - philo->info->start + 1;
		else
			n = philo->last_action;
		if (type != 666)
			ft_putnbr_fd(n, 1);
		ft_putstr_fd("\t", 1);
		ft_display_message2(philo, type, 1);
		z = ft_printf_str(type);
		if (type == 666)
			ft_display_message2(philo, type, 2);
		if (z == 'Y')
			pthread_mutex_unlock(&philo->info->somebody_dead_m);
	}
	pthread_mutex_unlock(&philo->info->write_m);
	return (0);
}
