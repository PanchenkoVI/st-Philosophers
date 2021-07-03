/*
* Created: 2021/03/24
*/

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct		s_opt
{
	int				amount;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				must_eat_count;
	int				stop_eat;
}					t_opt;

typedef struct		s_one
{
	int				position;
	int				lfork;
	int				rfork;
	int				eat_count;
	int				is_eating;
	size_t			last_action;
	size_t			limit;
	size_t			st;
	struct s_info	*info;
	struct s_opt	*opt;
	struct timeval	tv;
	pthread_mutex_t	turn;
	pthread_mutex_t	eat_m;
}					t_one;

typedef struct		s_info
{
	size_t			start;
	t_one			*p_one;
	t_opt			opt;
	pthread_t		tid;
	pthread_mutex_t	*forks_m;
	pthread_mutex_t	write_m;
	pthread_mutex_t	write_tm;
	pthread_mutex_t	somebody_dead_m;
}					t_info;

int					ft_strlen(const char *str);
int					ft_atoi(const char *str);
int					ft_printf_str(int n);
int					ft_display_message(t_one *philo, int type);
int					ft_time(t_one *philo, int i);
int					ft_cycle_r(t_one *philo);
int					ft_threads(t_info *info, int i);
int					ft_timer(t_one *philo);
int					init(t_info *info, int i);
int					ft_check_malloc(t_info *info);
int					ft_base(t_info inf);
int					main(int argc, char **argv);
int					ft_cercl(char *str, int i);
int					ft_analysus_date_arg2(t_info *inf, char **argv, int argc);
int					ft_analysus_date_arg(t_info *inf, \
						char **argv, int argc, int ar_die);
int					ft_analysis_arg(t_info *inf, int argc, char **argv);
void				*ft_monitor_count(void *inf);
void				*ft_monitor(void *philo_v);
void				*ft_routine(void *philo_v);
void				ft_cycle_clear(t_info *info, int i, int n);
void				ft_clear_struct(t_info *info, int i);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr_fd(unsigned long n, int fd);
void				ft_putstr_fd(char *s, int fd);
char				*ft_itoa(unsigned long nbr, int base, int len, char *str);
char				*ft_strdup(const char *s1);

#endif
