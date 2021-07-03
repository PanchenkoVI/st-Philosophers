/*
* Created: 2021/03/24
*/

#include "../header/philo_three.h"

void	ft_putstr_fd(char *s, int fd)
{
	int		i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
	}
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		n;

	n = 0;
	while (s1[n] != '\0')
		n++;
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	n = 0;
	while (s1[n])
	{
		str[n] = s1[n];
		n++;
	}
	str[n] = '\0';
	return (str);
}

int		ft_strlen(const char *str)
{
	int		i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}
