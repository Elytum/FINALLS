#include "../includes/ft_ls.h"
#include <unistd.h>









void		ft_putfilesdebug(t_file *head, int flags, t_times times)
{
	t_file	*ptr;
	char	*buff;
	char	*tmp;
	char	*p;
	char	lens[7];
	int		len;

	if (!(buff = (char *)ft_memalloc(sizeof(char) * 256)))
		return ;
	if (flags & LL_FLAG && !(flags & UC_FLAG))
	{
		ptr = head;
		while (ptr)
		{
			ptr->pw = getpwuid(ptr->filestat.st_uid);
			ptr->gr = getgrgid(ptr->filestat.st_gid);
			if (!ptr->pw || !(ptr->owner = ptr->pw->pw_name))
				ptr->owner = ft_itoa(ptr->filestat.st_uid);
			if (!ptr->gr || !(ptr->group = ptr->gr->gr_name))
				ptr->group = ft_itoa(ptr->filestat.st_gid);
			ptr = ptr->next;
		}
		ft_getlens(head, &lens);
		lens[4] = 11 + lens[0] + lens[1] + lens[2] + lens[3] + 7 + 13;
		if (lens[5] || lens[6])
			lens[4] += lens[5] + lens[6] + 2;
		if (!(tmp = (char *)malloc(sizeof(char) * (lens[4] + 1))))
			return ;
		*(tmp + lens[4]) = '\0';
	}
	ptr = head;
	while (ptr)
	{
		if (flags & LM_FLAG)
		{
			write(1, ptr->name, ft_strlen(ptr->name));
			if (ptr->next)
				write(1, ", ", 2);
			else
				write(1, "\n", 1);
		}
		else if (flags & LL_FLAG && !(flags & UC_FLAG))
		{
			ft_memset(tmp, ' ', lens[4]);
			p = tmp;
			p += 11;
			ft_put_onwork_permissions(ptr->filestat.st_mode, p - 1, ptr->path);
			p += lens[0];
			ft_put_onwork_value(ptr->filestat.st_nlink, p);
			p += 2;
			ft_put_onwork_owner(ptr->owner, p);
			p += lens[1];
			p += 2;
			ft_put_onwork_group(ptr->group, p);
			p += lens[2] + lens[3] + 1;
			if (lens[5] || lens[6])
			{
				p += lens[5] + lens[6] + 2;
				if (ptr->major && ptr->minor)
					ft_put_devices(ptr->major, ptr->minor, lens[6], p);
				else
					ft_put_onwork_value(ptr->filestat.st_size, p);
			}
			else
				ft_put_onwork_value(ptr->filestat.st_size, p);
			p += 2;
			ft_put_onwork_time(ptr->filestat, ptr->date, times, p);
			write(1, tmp, lens[4]);
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
		else
		{
			len = ft_strlen(ptr->name);
			write(1, ptr->name, len);
			ft_put_after(ptr, flags);
			write(1, "\n", 1);
		}
		ptr = ptr->next;
	}
	if (flags & LL_FLAG && !(flags & UC_FLAG))
		free(tmp);
	free(buff);
}
