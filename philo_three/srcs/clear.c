/*
* Created: 2021/03/24
*/

#include "../header/philo_three.h"

void	ft_clear_struct(t_info *info)
{
	sem_unlink("fork");
	sem_unlink("write");
	sem_unlink("dead");
	sem_unlink("stop");
	if (info->p_three)
	{
		sem_unlink("eat");
		free(info->p_three);
	}
}
