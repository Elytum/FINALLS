/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 04:49:41 by achazal           #+#    #+#             */
/*   Updated: 2014/11/25 22:54:45 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*ft_strrchr(const char *s, int c)
{
	char	letter;
	int		i;

	i = 0;
	while (s[i])
		i++;
	letter = (char)c;
	while (i && s[i] != letter)
	{
		i--;
	}
	if (s[i] == letter)
		return ((char *)s + i);
	return (0);
}
