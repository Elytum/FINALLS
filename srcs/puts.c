/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 04:49:41 by achazal           #+#    #+#             */
/*   Updated: 2014/11/25 22:54:45 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void			ft_getlens_init(char lens[][7])
{
	(*lens)[0] = 0;
	(*lens)[1] = 0;
	(*lens)[2] = 0;
	(*lens)[3] = 0;
	(*lens)[4] = 0;
	(*lens)[5] = 0;
	(*lens)[6] = 0;
}

static void			begin_loop(char lens[][7], t_file *ptr)
{
	char			tmp;

	tmp = ft_intlen(ptr->filestat.st_nlink);
	if ((*lens)[0] < tmp)
		(*lens)[0] = tmp;
	tmp = ft_strlen(ptr->owner);
	if ((*lens)[1] < tmp)
		(*lens)[1] = tmp;
	tmp = ft_strlen(ptr->group);
	if ((*lens)[2] < tmp)
		(*lens)[2] = tmp;
	tmp = ft_intlen(ptr->filestat.st_size);
	if ((*lens)[3] < tmp)
		(*lens)[3] = tmp;
}

void				ft_getlens(t_file *head, char lens[][7])
{
	t_file			*ptr;
	char			tmp;

	ft_getlens_init(lens), ptr = head;
	while (ptr)
	{
		begin_loop(lens, ptr);
		if (S_ISCHR(ptr->filestat.st_mode) || S_ISBLK(ptr->filestat.st_mode))
		{
			ptr->major = ft_itoa(major(ptr->filestat.st_rdev));
			ptr->minor = ft_itoa(minor(ptr->filestat.st_rdev));
			tmp = ft_strlen(ptr->major);
			if ((*lens)[5] < tmp)
				(*lens)[5] = tmp;
			tmp = ft_strlen(ptr->minor);
			if ((*lens)[6] < tmp)
				(*lens)[6] = tmp;
		}
		else
		{
			ptr->major = NULL;
			ptr->minor = NULL;
		}
		ptr = ptr->next;
	}
}

void				second_step_1(char **tmp, char **p,
									char lens[7], t_file *ptr)
{
	ft_memset((*tmp), ' ', lens[4]);
	(*p) = *tmp;
	(*p) += 11;
	ft_put_onwork_permissions(ptr->filestat.st_mode, (*p) - 1, ptr->path);
	(*p) += lens[0];
	ft_put_onwork_value(ptr->filestat.st_nlink, (*p));
	(*p) += 2;
	ft_put_onwork_owner(ptr->owner, (*p));
	(*p) += lens[1];
	(*p) += 2;
	ft_put_onwork_group(ptr->group, (*p));
	(*p) += lens[2] + lens[3] + 1;
	if (lens[5] || lens[6])
	{
		(*p) += lens[5] + lens[6] + 2;
		if (ptr->major && ptr->minor)
			ft_put_devices(ptr->major, ptr->minor, lens[6], (*p));
		else
			ft_put_onwork_value(ptr->filestat.st_size, (*p));
	}
	else
		ft_put_onwork_value(ptr->filestat.st_size, (*p));
	*p += 2;
}

void				second_step_2(int flags, char *buff, t_file *ptr)
{
	int				len;

	len = ft_strlen(ptr->name);
	write(1, ptr->name, len);
	ft_put_after(ptr, flags);
	if (S_ISLNK(ptr->filestat.st_mode))
	{
		write(1, " -> ", 4);
		readlink(ptr->path, buff, 256);
		write(1, buff, ft_strlen(buff));
		ft_strclr(buff);
	}
	write(1, "\n", 1);
}
