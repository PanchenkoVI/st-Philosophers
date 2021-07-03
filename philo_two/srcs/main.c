/*
* Created: 2021/03/24
*/

#include "../header/philo_two.h"

void		*ft_monitor_count(void *inf)
{
	t_info		*info;
	int			i;
	int			n;

	info = (t_info*)inf;
	n = 0;
	while (n < info->opt.must_eat_count)
	{
		i = 0;
		while (i < info->opt.amount)
		{
			if (sem_wait(info->p_two[i].eat_count_m))
				return ((void*)0);
			i++;
		}
		n++;
	}
	if (ft_display_message(&info->p_two[0], 666, 1, 0))
		return ((void*)0);
	if (sem_post(info->somebody_dead_m))
		return ((void*)0);
	return ((void*)0);
}

static int	ft_smph(t_info *info)
{
	sem_unlink("dead");
	info->somebody_dead_m = sem_open("dead", O_CREAT, 0777, 0);
	sem_unlink("block");
	info->for_time = sem_open("block", O_CREAT, 0777, 1);
	sem_unlink("write");
	info->write_m = sem_open("write", O_CREAT, 0777, 1);
	sem_unlink("fork");
	info->forks_m = sem_open("fork", O_CREAT, 0777, info->opt.amount);
	return (0);
}

static int	init(t_info *info, int i)
{
	while (i < info->opt.amount)
	{
		info->p_two[i].eat_count = 0;
		info->p_two[i].is_eating = 0;
		info->p_two[i].position = i;
		info->p_two[i].info = info;
		info->p_two[i].print_time = 0;
		sem_unlink("eat");
		info->p_two[i].eat_count_m = sem_open("eat", O_CREAT, 0777, 0);
		i++;
	}
	ft_smph(info);
	return (0);
}

int			ft_base(t_info *inf)
{
	if (!(inf->p_two = (t_two*)malloc(sizeof(*(inf->p_two)) * \
		inf->opt.amount)))
	{
		ft_printf_str(-2);
		return (1);
	}
	if (init(inf, 0))
	{
		ft_printf_str(-3);
		return (1);
	}
	if (ft_start_threads(inf, 0))
	{
		ft_printf_str(-4);
		return (1);
	}
	sem_wait(inf->somebody_dead_m);
	ft_clear_struct(inf);
	return (0);
}

int			main(int argc, char **argv)
{
	t_info		inf;
	int			i;

	if ((i = ft_analysis_arg(&inf, argc, argv)) == -1)
		return (1);
	if (ft_base(&inf))
	{
		ft_clear_struct(&inf);
		return (1);
	}
	return (0);
}
