#include <stdlib.h>
#include <unistd.h>

void		ft_putsize_t(size_t n)
{
	char	c;

	if (n >= 10)
	{
		ft_putsize_t(n / 10);
		c = n % 10 + '0';
		write(1, &c, 1);
	}
	else
	{
		c = n + '0';
		write(1, &c, 1);
	}
}
