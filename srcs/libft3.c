/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 04:49:41 by achazal           #+#    #+#             */
/*   Updated: 2015/05/10 12:09:37 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	return (len);
}

void				*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*way;

	way = (unsigned char *)b;
	while (len--)
		*way++ = c;
	return (b);
}

char				*ft_strcpyo(char *dst, const char *src)
{
	char			*ptr;
	char			*p;

	p = dst;
	ptr = (char *)src;
	while (*ptr)
		*p++ = *ptr++;
	return (dst);
}

char				*ft_strncpyo(char *dst, const char *src, size_t n)
{
	char			*ptr;
	char			*p;

	p = dst;
	ptr = (char *)src;
	while (n-- && *ptr)
		*p++ = *ptr++;
	return (dst);
}
