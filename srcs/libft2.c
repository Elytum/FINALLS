/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 04:49:41 by achazal           #+#    #+#             */
/*   Updated: 2014/11/25 22:54:45 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/ft_ls.h"

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

char        *ft_ltoa(long long int n)
{
    char    *str;
    char    *new;
    int     pos;
    int     tmp;

    pos = 0;
    tmp = n;
    if (n == -9223372036854775807 || n == 0)
        return ((n == 0) ? ft_strdup("0") : ft_strdup("-9223372036854775807"));
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

char		*ft_strrev(char *str)
{
	char	*dst;
	int		len;
	int		i;

	len = ft_strlen(str);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		dst[i] = str[len - i - 1];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char		*ft_strcpy(char *dst, const char *src)
{
	size_t	c;

	c = 0;
	while (src[c])
	{
		dst[c] = src[c];
		c++;
	}
	dst[c] = '\0';
	return (dst);
}
