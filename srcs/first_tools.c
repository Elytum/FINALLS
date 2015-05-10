/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 04:49:41 by achazal           #+#    #+#             */
/*   Updated: 2014/11/25 22:54:45 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <unistd.h>

DIR					*ft_directory_intro(char *dir, int *flags,
											char **ptr, t_info *info)
{
	DIR				*dirp;
	int				len;

	len = ft_strlen(dir);
	if (*flags & FIRST)
		*flags &= ~FIRST;
	else
		write(1, "\n", 1);
	if (!(*flags & SINGLE))
		write(1, dir, len), write(1, ":\n", 2);
	else
		*flags &= ~SINGLE;
	if (!(info->path = (char *)malloc(sizeof(char) * (256 + len))))
		return (NULL);
	if (!(dirp = opendir(dir)))
	{
		free(info->path);
		ft_put_permission_denied(dir);
		return (NULL);
	}
	*ptr = info->path + len;
	ft_strcpy(info->path, dir);
	**ptr = '/', (*ptr)++;
	**ptr = '\0';
	return (dirp);
}

t_file				*ft_directory_loop(char **dir, int *flags, compare f)
{
	DIR				*dirp;
	struct dirent	*direntp;
	t_info			info;
	t_file			*files;
	char			*ptr;

	if (!(dirp = ft_directory_intro(*dir, flags, &ptr, &info)))
		return (NULL);
	files = NULL;
	while ((direntp = readdir(dirp)))
	{
		if (direntp == NULL)
			break ;
		if (*flags & LA_FLAG || direntp->d_name[0] != '.')
		{
			info.name = direntp->d_name;
			ft_strcpy(ptr, direntp->d_name);
			ft_add_new_file2(&files, info, f, *flags);
		}
	}
	closedir(dirp);
	free(info.path);
	if (*flags & LL_FLAG)
		ft_puttotal(files);
	return (files);
}

void				ft_manage_directory(char *dir, compare f,
											int flags, t_times times)
{
	char			**paths;
	char			**pptr;
	t_file			*files;

	if (!(files = ft_directory_loop(&dir, &flags, f)))
		return ;
	ft_putfilesdebug(files, flags, times);
	paths = ft_extractpaths(files);
	ft_freefiles2(&files, flags);
	if (flags & UR_FLAG && paths)
	{
		pptr = paths;
		while (*pptr)
		{
			ft_manage_directory(*pptr, f, flags, times);
			free(*pptr++);
		}
	}
	else
	{
		pptr = paths;
		while (*pptr)
			free(*pptr++);
	}
	free(paths);
}
