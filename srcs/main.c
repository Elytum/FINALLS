/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 04:49:41 by achazal           #+#    #+#             */
/*   Updated: 2014/11/25 22:54:45 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <time.h>

char		ft_init(int *flags, compare *f, int ac, char ***av)
{
	char	**ptr;

	ptr = *av + 2;
	while (*ptr)
	{
		if (!**ptr)
		{
			write (1, "ls: fts_open: No such file or directory\n", 40);
			return (0);
		}
		ptr++;
	}
	(*av)++;
	if (ac > 1 && (*flags = ft_getflags(av)) & ERROR)
		return (0);
	ft_interact_flags(flags);
	*f = ft_get_function(*flags);
	*flags |= SINGLE;
	*flags |= FIRST;
	return (1);
}

int			main(int ac, char **av)
{
	int		flags;
	t_times times;
	compare	f;

	times.launchtime = time(NULL);
	times.timelimit = times.launchtime - 15638400;
	if (!ft_init(&flags, &f, ac, &av))
		return (0);
	if (!*av)
	{
		av = (char **)malloc(sizeof(char *) * 2);
		*av = ft_strdup(".");
		*(av + 1) = NULL;
		ft_manage_first(av, f, flags, times);
		free(*av);
		free(av);
	}
	else
		ft_manage_first(av, f, flags, times);
	return (0);
}
