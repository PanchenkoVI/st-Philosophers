/*
* Created: 2021/03/24
*/

#include "../header/philo_one.h"

void	ph_mtx_init(t_info *info)
{
	pthread_mutex_init(&info->somebody_dead_m, NULL);
	pthread_mutex_init(&info->write_m, NULL);
	pthread_mutex_init(&info->write_tm, NULL);
}

int		init(t_info *info, int i)
{
	while (i < info->opt.amount)
	{
		info->p_one[i].eat_count = 0;
		info->p_one[i].is_eating = 0;
		info->p_one[i].lfork = i;
		info->p_one[i].st = 0;
		info->p_one[i].position = i;
		if (i % 2 == 0)
			info->p_one[i].rfork = i + 1;
		else
			info->p_one[i].rfork = i - 1;
		info->p_one[i].info = info;
		pthread_mutex_init(&info->p_one[i].eat_m, NULL);
		if (pthread_mutex_lock(&info->p_one[i].eat_m))
			return (1);
		i++;
	}
	ph_mtx_init(info);
	if (pthread_mutex_lock(&info->somebody_dead_m))
		return (1);
	i = 0;
	while (i < info->opt.amount)
		pthread_mutex_init(&info->forks_m[i++], NULL);
	return (0);
}

int		ft_check_malloc(t_info *info)
{
	if (!(info->p_one = (t_one*)malloc(sizeof(*(info->p_one)) * \
		info->opt.amount)))
		return (1);
	if (!(info->forks_m = (pthread_mutex_t*)malloc(sizeof(*(info->forks_m)) * \
		info->opt.amount)))
		return (1);
	return (0);
}

int		ft_base(t_info inf)
{
	if (ft_check_malloc(&inf) == 1)
	{
		ft_printf_str(-2);
		return (1);
	}
	if (init(&inf, 0))
	{
		ft_printf_str(-3);
		return (1);
	}
	if (ft_threads(&inf, 0))
	{
		ft_printf_str(-4);
		return (1);
	}
	pthread_mutex_lock(&inf.somebody_dead_m);
	pthread_mutex_unlock(&inf.somebody_dead_m);
	ft_clear_struct(&inf, 0);
	return (0);
}

int		main(int argc, char **argv)
{
	t_info	inf;
	int		i;

	if ((i = ft_analysis_arg(&inf, argc, argv)) == -1)
		return (1);
	if (ft_base(inf))
		return (1);
	return (0);
}
