/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 04:49:41 by achazal           #+#    #+#             */
/*   Updated: 2014/11/25 22:54:45 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t				ft_strlen(char *str)
{
	char			*ptr;

	ptr = str;
	while (*ptr)
		ptr++;
	return (ptr - str);
}

char				*ft_strdup(char *str)
{
	register char	*strnew;
	register char	*ptr;

	if (!(strnew = (char *)malloc(sizeof(char) * ft_strlen(str) + 1)))
		return (NULL);
	ptr = strnew;
	while (*str)
		*ptr++ = *str++;
	*ptr = '\0';
	return (strnew);
}

int					ft_strcmp(const char *s1, const char *s2)
{
	if (!s1)
		return ((unsigned char)*s2);
	if (!s2)
		return ((unsigned char)*s1);
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
