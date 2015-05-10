/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparisons2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 04:49:41 by achazal           #+#    #+#             */
/*   Updated: 2014/11/25 22:54:45 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int				ft_cmpdate(t_file *s1, t_file *s2)
{
	time_t		ret;

	ret = s2->filestat.st_mtime - s1->filestat.st_mtime;
	if (!ret)
		return (ft_strcmp(s1->name, s2->name));
	if (ret > 0)
		return (1);
	return (-1);
}

int				ft_cmprdate(t_file *s1, t_file *s2)
{
	time_t		ret;

	ret = s1->filestat.st_mtime - s2->filestat.st_mtime;
	if (!ret)
		return (ft_strcmp(s2->name, s1->name));
	if (ret > 0)
		return (-1);
	return (1);
}

int				ft_cmpsize(t_file *s1, t_file *s2)
{
	int			ret;

	if (!(ret = s2->filestat.st_size - s1->filestat.st_size))
		ret = ft_strcmp(s1->name, s2->name);
	return (ret);
}

int				ft_cmprsize(t_file *s1, t_file *s2)
{
	int			ret;

	if (!(ret = s1->filestat.st_size - s2->filestat.st_size))
		ret = ft_strcmp(s2->name, s1->name);
	return (ret);
}
