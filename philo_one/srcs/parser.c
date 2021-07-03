/*
* Created: 2021/03/24
*/

#include "../header/philo_one.h"

int		ft_cercl(char *str, int i)
{
	while (str[i])
	{
		if (str[i] > 47 && str[i] < 58)
			i++;
		else
		{
			i = -1;
			break ;
		}
	}
	return (i);
}

int		ft_analysus_date_arg2(t_info *inf, char **argv, int argc)
{
	int		ar_mb;
	int		ar_sleep;

	ar_sleep = ft_atoi(argv[4]);
	if (ar_sleep < 60)
		return (-1);
	inf->opt.time_to_sleep = ar_sleep;
	if (argc == 6)
	{
		ar_mb = ft_atoi(argv[5]);
		if (ar_mb < 0)
			return (-1);
		inf->opt.must_eat_count = ar_mb;
	}
	else
		inf->opt.must_eat_count = -1;
	inf->opt.stop_eat = inf->opt.must_eat_count;
	return (0);
}

int		ft_analysus_date_arg(t_info *inf, char **argv, int argc, int ar_die)
{
	int count;
	int ar_eat;

	count = ft_atoi(argv[1]);
	if (count < 2 || count > 200)
		return (-1);
	inf->opt.amount = count;
	ar_die = ft_atoi(argv[2]);
	if (ar_die < 60)
		return (-1);
	inf->opt.time_to_die = ar_die;
	ar_eat = ft_atoi(argv[3]);
	if (ar_eat < 60)
		return (-1);
	inf->opt.time_to_eat = ar_eat;
	if (ft_analysus_date_arg2(inf, argv, argc) == -1)
		return (-1);
	return (0);
}

int		ft_analysis_arg(t_info *inf, int argc, char **argv)
{
	int i;

	i = 1;
	if (argc != 5 && argc != 6)
		i = -1;
	if (i == 1)
	{
		while (argv[i])
		{
			if (ft_cercl(argv[i], 0) < 0)
			{
				i = -1;
				break ;
			}
			i++;
		}
	}
	if (i != -1 && ft_analysus_date_arg(inf, argv, argc, 0) < 0)
		i = -1;
	if (i == -1)
		ft_printf_str(-1);
	return (i);
}
