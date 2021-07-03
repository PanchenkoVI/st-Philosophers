/*
* Created: 2021/03/24
*/

#include "../header/philo_two.h"

int		ft_atoi(const char *str)
{
	int		i;
	int		n;
	long	nb;

	n = 1;
	nb = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			n = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (nb * n > 2147483647)
			return (-1);
		if (nb * n < -2147483648)
			return (0);
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (nb * n);
}

char	*ft_itoa(unsigned long nbr, int base, int len, char *str)
{
	unsigned long tmp;

	tmp = nbr;
	if (nbr == 0)
		len++;
	while (tmp > 0)
	{
		tmp /= base;
		len++;
	}
	if (!(str = (char*)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	str[len] = '\0';
	while (len > 0)
	{
		str[len - 1] = nbr % base;
		if (nbr % base > 9)
			str[len - 1] += 'a' - 10;
		else
			str[len - 1] += '0';
		nbr /= base;
		len--;
	}
	return (str);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(unsigned long n, int fd)
{
	unsigned int	ch;
	char			c;

	c = 0;
	ch = n;
	if (ch >= 10)
		ft_putnbr_fd(ch / 10, fd);
	c = (ch % 10) + 48;
	write(fd, &c, 1);
}
