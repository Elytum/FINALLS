/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putfiles.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 04:49:41 by achazal           #+#    #+#             */
/*   Updated: 2014/11/25 22:54:45 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void init_bigbadass(char **buff, char **tmp, int flags, char lens[7])
{
	if (!((*buff) = (char *)ft_memalloc(sizeof(char) * 256)))
		return ;
	if (flags & LL_FLAG && !(flags & UC_FLAG))
	{
		if (!((*tmp) = (char *)malloc(sizeof(char) * (lens[4]))))
			return ;
		*((*tmp) + lens[4]) = '\0';
	}
}

static void	partone(char **p, char **tmp, char lens[7], t_file *ptr)
{
	ft_memset((*tmp), ' ', lens[4]);
	(*p) = (*tmp);
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
	(*p) += 2;
}

static void	parttwo(char *tmp, char *buff, char lens[7], t_file *ptr)
{
	write(1, tmp, lens[4]), write(1, ptr->name, ft_strlen(ptr->name));
	if (S_ISLNK(ptr->filestat.st_mode))
	{
		write(1, " -> ", 4), readlink(ptr->path, buff, 256);
		write(1, buff, ft_strlen(buff)), ft_strclr(buff);
	}
	write(1, "\n", 1);
}

static void	ft_bigbadassloop(int flags, t_file *ptr,
				t_times times, char lens[7])
{
	char	*buff;
	char	*tmp;
	char	*p;

	init_bigbadass(&buff, &tmp, flags, lens);
	while (ptr)
	{
		if (S_ISREG(ptr->filestat.st_mode) || (S_ISLNK(ptr->filestat.st_mode)
			&& (flags & LL_FLAG)) || ft_isnotlinktodir(ptr->path,
				ptr->filestat.st_mode))
		{
			if (flags & LL_FLAG && !(flags & UC_FLAG))
			{
				partone(&p, &tmp, lens, ptr);
				ft_put_onwork_time(ptr->filestat, ptr->date, times, p);
				parttwo(tmp, buff, lens, ptr);
			}
			else
				write(1, ptr->name, ft_strlen(ptr->name)), write(1, "\n", 1);
		}
		ptr = ptr->next;
	}
	if (flags & LL_FLAG && !(flags & UC_FLAG))
		free(tmp);
	free(buff);
}

void		ft_putfiles(t_file *head, int flags, t_times times)
{
	t_file	*ptr;
	char	lens[7];

	if (flags & LL_FLAG && !(flags & UC_FLAG))
	{
		ptr = head;
		while (ptr)
		{
			ptr->pw = getpwuid(ptr->filestat.st_uid);
			ptr->gr = getgrgid(ptr->filestat.st_gid);
			if (flags & LN_FLAG || !ptr->pw || !(ptr->owner = ptr->pw->pw_name))
				ptr->owner = ft_itoa(ptr->filestat.st_uid);
			if (flags & LN_FLAG || !ptr->gr || !(ptr->group = ptr->gr->gr_name))
				ptr->group = ft_itoa(ptr->filestat.st_gid);
			ptr = ptr->next;
		}
		ft_getlens(head, &lens);
		lens[4] = 11 + lens[0] + lens[1] + lens[2] + lens[3] + 7 + 13;
		if (lens[5] || lens[6])
			lens[4] += lens[5] + lens[6] + 2;
	}
	ft_bigbadassloop(flags, head, times, lens);
}
