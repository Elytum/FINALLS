/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getflags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 04:49:41 by achazal           #+#    #+#             */
/*   Updated: 2014/11/25 22:54:45 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <unistd.h>

void		ft_putfiles(char **av)
{
	char	**ptr;

	ptr = av;
	while (*ptr)
	{
		write(1, *ptr, ft_strlen(*ptr));
		write(1, "\n", 1);
		ptr++;
	}
}

void		ft_manage_first(char **args, char flags)
{
	t_paths	*paths;
	char	**ptr;

	paths = NULL;
	ptr = args;
	while (*ptr)
	{
		ft_addpath(&paths, *ptr);
		ptr++;
	}
	ft_cleanpath(&paths);
	ft_putpath(paths);
	(void)flags;
}

int			main(int ac, char **av)
{
	char	flags;

	flags = 0;

	if (ac > 1 && (flags = ft_getflags(&av)) & ERROR)
		return (0);
	if (!*av)
	{
		av = (char **)malloc(sizeof(char *) * 2);
		*av = ft_strdup(".");
		*(av + 1) = NULL;
	}
	ft_testflags(flags);
	ft_manage_first(av, flags);
	return (0);
}
