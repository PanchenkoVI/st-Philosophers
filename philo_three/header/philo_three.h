/*
* Created: 2021/03/24
*/

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct		s_opt
{
	int				amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				stop_eat;
}					t_opt;

typedef struct		s_two
{
	pid_t			pid;
	int				position;
	int				is_eating;
	size_t			lll;
	size_t			limit;
	size_t			last_eat;
	size_t			print_time;
	int				eat_count;
	struct s_info	*info;
	struct s_opt	*opt;
	struct timeval	tv;
	int				lfork;
	int				rfork;
	sem_t			*mutex;
	sem_t			*eat_count_m;
}					t_three;

typedef struct		s_info
{
	size_t			start;
	t_three			*p_three;
	t_opt			opt;
	pthread_t		tid;
	sem_t			*for_time;
	sem_t			*forks_m;
	sem_t			*write_m;
	sem_t			*somebody_dead_m;
	sem_t			*dead_write_m;
}					t_info;

int					ft_atoi(const char *str);
char				*ft_itoa(unsigned long nbr, int base, int len, char *str);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr_fd(unsigned long n, int fd);
char				*ft_strdup(const char *s1);
int					ft_strlen(const char *str);
void				ft_putstr_fd(char *s, int fd);
int					ft_analysis_arg(t_info *inf, int argc, char **argv);
int					ft_start_process(t_info *info);
int					ft_printf_str(int n);
void				ft_clear_struct(t_info *info);
void				ft_display_message(t_three *philo, int type, size_t n);
int					ft_cycle_r(t_three *philo);
int					ft_base(t_info *inf, int i);
int					main(int argc, char **argv);

#endif
