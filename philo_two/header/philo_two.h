/*
* Created: 2021/03/24
*/

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>

typedef struct		s_opt
{
	int				amount;
	int				must_eat_count;
	int				stop_eat;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
}					t_opt;

typedef struct		s_two
{
	int				position;
	size_t			is_eating;
	size_t			limit;
	size_t			lll;
	size_t			print_time;
	size_t			last_eat;
	size_t			eat_count;
	struct s_info	*info;
	struct s_opt	*opt;
	struct timeval	tv;
	sem_t			*eat_count_m;
}					t_two;

typedef struct		s_info
{
	size_t			start;
	t_two			*p_two;
	t_opt			opt;
	sem_t			*for_time;
	sem_t			*forks_m;
	sem_t			*write_m;
	sem_t			*somebody_dead_m;
	pthread_t		tid;
}					t_info;

int					ft_strlen(const char *str);
int					ft_atoi(const char *str);
int					main(int argc, char **argv);
int					ft_cycle_r(t_two *philo);
int					ft_base(t_info *inf);
int					ft_analysis_arg(t_info *inf, int argc, char **argv);
int					ft_display_message(t_two *philo, int type, \
										int ind, size_t n);
int					ft_printf_str(int n);
int					ft_start_threads(t_info *info, int i);
void				ft_timer(t_two *philo);
void				*ft_monitor_count(void *inf);
void				ft_clear_struct(t_info *info);
void				ft_putstr_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr_fd(unsigned long n, int fd);
char				*ft_strdup(const char *s1);
char				*ft_itoa(unsigned long nbr, int base, int len, char *str);

#endif
