#include <stdlib.h>
#include <stdio.h>

void				*ft_memalloc(size_t size)
{
	void			*memory;
	unsigned int	counter;
	char			*explorer;

	counter = 0;
	if (!size)
		return (NULL);
	if (!(memory = (void *)malloc(size)))
		return (NULL);
	explorer = (char *)memory;
	if (memory != NULL)
	{
		while (counter++ < size)
			*explorer++ = 0;
	}
	return (memory);
}

int					ft_intlen(int n)
{
	int				len;

	// dprintf(1, "Len of %i = ", n);
	if (n == 0)
		return (1);
	else if (n == -2147483648)
		return (12);
	len = 0;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	// dprintf(1, "%i\n", len);
	return (len);
}

/*
char        *ft_itoa(int n)
{
    char    *str;
    char    *new;
    int     pos;
    int     tmp;

    pos = 0;
    tmp = n;
    if (n == -2147483648 || n == 0)
        return ((n == 0) ? ft_strdup("0") : ft_strdup("-2147483648"));
    if (!(str = (char *)malloc(sizeof(char) * 12)))
        return (NULL);
    if (n < 0)
        n *= -1;
    while (n > 0)
    {
        str[pos++] = (n % 10) + 48;
        n = n / 10;
    }
    str[pos] = '\0';
    (tmp < 0) ? (str[pos++] = '-') : 0;
    str[pos] = '\0';
    new = ft_strrev(str);
    free(str);
    return (new);
}
*/

void		ft_bzero(void *s, size_t n)
{
	unsigned char	*way;
	if (!n)
		return ;
	way = (unsigned char *)s;
	while (n--)
		*way++ = 0;
}

void				*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*way;

	i = 0;
	way = (unsigned char *)b;
	while (i < len)
		way[i++] = (unsigned char)c;
	return (b);
}

char		*ft_strcpyo(char *dst, const char *src)
{
			size_t	c;

	c = 0;
	while (src[c])
	{
		dst[c] = src[c];
		c++;
	}
	return (dst);
}

char		*ft_strncpyo(char *dst, const char *src, size_t n)
{
	size_t	c;

	c = 0;
	while (n-- && src[c])
	{
		dst[c] = src[c];
		c++;
	}
	return (dst);
}
