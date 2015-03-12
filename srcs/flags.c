/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 04:49:41 by achazal           #+#    #+#             */
/*   Updated: 2014/11/25 22:54:45 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <unistd.h>

void			ft_fillflag(char p, char *flags)
{
	if (p == 'l')
		(*flags) |= LL_FLAG;
	else if (p == 'R')
		(*flags) |= UR_FLAG;
	else if (p == 'a')
		(*flags) |= LA_FLAG;
	else if (p == 'r')
		(*flags) |= LR_FLAG;
	else if (p == 't')
		(*flags) |= LT_FLAG;
	else
	{
		write (1, ILLEGAL_OPTION, ILLEGAL_OPTION_SIZE);
		write (1, &p, 1);
		write (1, USAGE, USAGE_SIZE);
		(*flags) |= ERROR;
	}
}

char			ft_getflags(char ***str)
{
	char		flags;
	char		*p;

	flags = 0;
	while (*(*str))
	{
		if (**(*str) != '-')
			return (flags);
		if ((**(*str) == '-' && *(*(*str) + 1) == '-'))
		{
			if (*(*(*str)++ + 2))
				write (1, LLERROR, LLERROR_SIZE), flags |= ERROR;
			return (flags);
		}
		p = *(*str)++ + 1;
		while (*p)
		{
			ft_fillflag(*p, &flags);
			if (flags & ERROR)
				return (flags);
			p++;
		}
	}
	return (flags);
}

void			ft_testflags(char flags)
{
	if (flags & LL_FLAG)
		write(1, "l_Flag detected\n", 16);
	if (flags & UR_FLAG)
		write(1, "R_Flag detected\n", 16);
	if (flags & LA_FLAG)
		write(1, "a_Flag detected\n", 16);
	if (flags & LR_FLAG)
		write(1, "r_Flag detected\n", 16);
	if (flags & LT_FLAG)
		write(1, "t_Flag detected\n", 16);
}
