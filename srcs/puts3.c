/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 04:49:41 by achazal           #+#    #+#             */
/*   Updated: 2014/11/25 22:54:45 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <unistd.h>
#include <ft_ls.h>

void		ft_put_permission_denied(char *path)
{
	char	*ptr;
	char	*p;

	ptr = path;
	while (*ptr)
		ptr++;
	while (*ptr != '/' && ptr != path)
		ptr--;
	if (*ptr == '/')
		ptr++;
	p = ptr;
	while (*p)
		p++;
	write(2, "ls: ", 4);
	write(2, ptr, p - ptr);
	write(2, ": Permission denied\n", 20);
}

void		ft_put_after(t_file *file, int flags)
{
	if (flags & UF_FLAG)
	{
		if (file->filestat.st_mode & S_IFDIR)
			write(1, "/", 1);
		else if (S_ISLNK(file->filestat.st_mode))
			write(1, "@", 1);
		else if (S_ISSOCK(file->filestat.st_mode))
			write(1, "=", 1);
		else if (S_ISFIFO(file->filestat.st_mode))
			write(1, "|", 1);
		else if (file->filestat.st_mode & S_IXUSR)
			write(1, "*", 1);
	}
	else if (flags & LP_FLAG)
		if (file->filestat.st_mode & S_IFDIR)
			write(1, "/", 1);
}

void		ft_put_onwork_owner(char *name, char *path)
{
	if (!name)
		return ;
	ft_strcpyo(path, name);
}

void		ft_put_onwork_group(char *group, char *path)
{
	if (!group)
		return ;
	ft_strcpyo(path, group);
}

void		ft_put_onwork_time(BYPASS filestat,
					time_t date, t_times times, char *path)
{
	if (date > times.timelimit && date <= time(NULL))
		ft_strncpyo(path, ctime(&(filestat).st_mtime) + 4, 12);
	else
	{
		ft_strncpyo(path, ctime(&(filestat).st_mtime) + 4, 7);
		ft_strncpyo(path + 8, ctime(&(filestat).st_mtime) + 20, 4);
	}
}
