/*
* Created: 2021/03/24
*/

#include "../header/philo_two.h"

void	ft_clear_struct(t_info *info)
{
	sem_unlink("fork");
	sem_unlink("write");
	sem_unlink("dead");
	sem_unlink("block");
	if (info->p_two)
	{
		sem_unlink("eat");
		free(info->p_two);
	}
}
