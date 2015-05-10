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
#include <stdio.h>

void			ft_fillflag(char p, int *flags)
{
	int			i;

	i = 0;
	while (g_tuple[i].opt)
	{
		if (g_tuple[i].opt == p)
		{
			*flags |= g_tuple[i].flag;
			return ;
		}
		++i;
	}
	write (2, ILLEGAL_OPTION, ILLEGAL_OPTION_SIZE);
	write (2, &p, 1);
	write (2, USAGE, USAGE_SIZE);
	(*flags) |= ERROR;
}

int			ft_getflags(char ***str)
{
	int		flags;
	char	*p;

	flags = 0;
	while (*(*str))
	{
		if (**(*str) != '-' || !*(*(*str) + 1))
			return (flags);
		if ((**(*str) == '-' && *(*(*str) + 1) == '-'))
		{
			if (*(*(*str)++ + 2))
				write (2, LLERROR, LLERROR_SIZE), flags |= ERROR;
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

void			ft_testflags(int flags)
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
	if (flags & US_FLAG)
		write(1, "S_Flag detected\n", 16);
	if (flags & UC_FLAG)
		write(1, "C_Flag detected\n", 16);
	if (flags & UF_FLAG)
		write(1, "F_Flag detected\n", 16);
	if (flags & LF_FLAG)
		write(1, "f_Flag detected\n", 16);
	if (flags & LM_FLAG)
		write(1, "m_Flag detected\n", 16);
	if (flags & LP_FLAG)
		write(1, "p_Flag detected\n", 16);
}
