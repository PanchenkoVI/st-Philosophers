/*
* Created: 2021/03/24
*/

#include "../header/philo_three.h"

static int	ft_smph(t_info *info)
{
	sem_unlink("dead");
	info->somebody_dead_m = sem_open("dead", O_CREAT, 0777, 0);
	sem_unlink("stop");
	info->dead_write_m = sem_open("stop", O_CREAT, 0777, 1);
	sem_unlink("write");
	info->write_m = sem_open("write", O_CREAT, 0777, 1);
	sem_unlink("fork");
	info->forks_m = sem_open("fork", O_CREAT, 0777, info->opt.amount);
	return (0);
}

static int	ft_init(t_info *info, int i)
{
	while (i < info->opt.amount)
	{
		info->p_three[i].is_eating = 0;
		info->p_three[i].lfork = i;
		info->p_three[i].position = i;
		info->p_three[i].print_time = 0;
		info->p_three[i].info = info;
		sem_unlink("eat");
		info->p_three[i].eat_count_m = sem_open("eat", O_CREAT, 0777, 0);
		i++;
	}
	ft_smph(info);
	return (0);
}

int			ft_base(t_info *inf, int i)
{
	if (!(inf->p_three = (t_three*)malloc(sizeof(*(inf->p_three)) * \
		inf->opt.amount)))
	{
		ft_printf_str(-2);
		return (1);
	}
	if (ft_init(inf, 0))
	{
		ft_printf_str(-3);
		return (1);
	}
	if (ft_start_process(inf))
	{
		ft_printf_str(-4);
		return (1);
	}
	sem_wait(inf->somebody_dead_m);
	while (i < inf->opt.amount)
		kill(inf->p_three[i++].pid, SIGKILL);
	ft_clear_struct(inf);
	return (0);
}

int			main(int argc, char **argv)
{
	t_info	inf;
	int		i;

	if ((i = ft_analysis_arg(&inf, argc, argv)) == -1)
		return (1);
	if (ft_base(&inf, 0))
	{
		ft_clear_struct(&inf);
		return (1);
	}
	return (0);
}
