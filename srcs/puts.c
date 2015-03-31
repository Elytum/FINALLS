#include "../includes/ft_ls.h"
#include <unistd.h>

void				ft_put_onwork_symbole(mode_t var, char *path)
{
	if (S_ISLNK(var))
		*path = 'l';
	else if ((var & 0170000) == 0040000)
		*path = 'd';
	else if ((var & 0170000) == 0020000)
		*path = 'c';
	else if ((var & 0170000) == 0060000)
		*path = 'b';
	else if ((var & 0170000) == 0010000)
		*path = 'p';
	else if ((var & 0170000) == 0140000)
		*path = 's';
	else
		*path = '-';
}

void				ft_put_onwork_permissions(mode_t var, char *path)
{
 	*path-- = ((var & S_IXOTH) ? 'x' : '-');
	*path-- = ((var & S_IWOTH) ? 'w' : '-');
	*path-- = ((var & S_IROTH) ? 'r' : '-');
	*path-- = ((var & S_IXGRP) ? 'x' : '-');
	*path-- = ((var & S_IWGRP) ? 'w' : '-');
	*path-- = ((var & S_IRGRP) ? 'r' : '-');
	*path-- = ((var & S_IXUSR) ? 'x' : '-');
	*path-- = ((var & S_IWUSR) ? 'w' : '-');
	*path-- = ((var & S_IRUSR) ? 'r' : '-');
	ft_put_onwork_symbole(var, path);
}

void				ft_put_onwork_value_loop(int n, char *path)
{
	if (n >= 10)
	{
		ft_put_onwork_value_loop(n / 10, path - 1);
		*path-- = n % 10 + '0';
	}
	else
		*path-- = n + '0';
}

void				ft_put_onwork_value(int n, char *path)
{
	if (n == -2147483648)
		ft_strcpyo(path, "-2147483648");
	else if (n == 0)
		ft_strcpyo(path, "0");
	else
	{
		if (n < 0)
		{
			*path-- = '-';
			n *= -1;
		}
		ft_put_onwork_value_loop(n, path);
	}
}

void				ft_put_onwork_owner(struct passwd *pw, char *path)
{
	if (!(pw))
		return ;
	ft_strcpyo(path, pw->pw_name);
}

void				ft_put_onwork_group(struct group *gr, char *path)
{
	if (!(gr))
		return ;
	ft_strcpyo(path, gr->gr_name);
}

void				ft_put_onwork_time(BYPASS filestat, int date, t_times times, char *path)
{
	if (date > times.timelimit && date < times.launchtime)
		ft_strncpyo(path, ctime(&(filestat).st_mtime) + 4, 12);
	else
	{
		ft_strncpyo(path, ctime(&(filestat).st_mtime) + 4, 7);
		ft_strncpyo(path + 8, ctime(&(filestat).st_mtime) + 20, 4);
	}
	// write(1, " ", 1);
}

void				ft_getlens(t_file *head, char lens[][5])
{
	t_file			*ptr;
	char			tmp;

	(*lens)[0] = 0;
	(*lens)[1] = 0;
	(*lens)[2] = 0;
	(*lens)[3] = 0;
	ptr = head;
	while (ptr)
	{
	// dprintf(1, "Owner is %s\n", ptr->name);
	// 	tmp = 2;
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
		// dprintf(1, "Size of %i = %i\n", (int)ptr->filestat.st_size, tmp);
		if ((*lens)[3] < tmp)
			(*lens)[3] = tmp;
		ptr = ptr->next;
	}
}


void		ft_putfiles(t_file *head, int flags, t_times times)
{
	t_file	*ptr;
	char	*buff;
	char	*tmp;
	char	*p;
	char	lens[5];

	if (!(buff = (char *)ft_memalloc(sizeof(char) * 256)))
		return ;
	if (flags & LL_FLAG && !(flags & UC_FLAG))
	{
		ptr = head;
		while (ptr)
		{
			ptr->pw = getpwuid(ptr->filestat.st_uid);
			ptr->gr = getgrgid(ptr->filestat.st_gid);
			ptr->owner = ptr->pw->pw_name;
			ptr->group = ptr->gr->gr_name;
			ptr = ptr->next;
		}
		ft_getlens(head, &lens);//1 + 1 + 2 + 2 + 1
		lens[4] = 11 + lens[0] + lens[1] + lens[2] + lens[3] + 7 + 13;
		if (!(tmp = (char *)malloc(sizeof(char) * (lens[4]))))
			return ;
		*(tmp + lens[4]) = '\0';
	}
	ptr = head;
	while (ptr)
	{
		if (S_ISREG(ptr->filestat.st_mode))
		{
			if (flags & LL_FLAG && !(flags & UC_FLAG))
			{
				ft_memset(tmp, ' ', lens[4]);
				p = tmp;
				p += 11;
				ft_put_onwork_permissions(ptr->filestat.st_mode, p - 2);
				p += lens[0];
				ft_put_onwork_value(ptr->filestat.st_nlink, p);
				p += 2;
				ft_put_onwork_owner(ptr->pw, p);
				p += lens[1];
				p += 2;
				ft_put_onwork_group(ptr->gr, p);
				p += lens[2] + lens[3] + 1;
				ft_put_onwork_value(ptr->filestat.st_size, p);
				p += 2;
				ft_put_onwork_time(ptr->filestat, ptr->date, times, p);
				write(1, tmp, lens[4]);

				write(1, ptr->name, ft_strlen(ptr->name));
				if (S_ISLNK(ptr->filestat.st_mode))
				{
					write(1, " -> ", 4);
					readlink(ptr->path, buff, 256);
					write(1, buff, 256);
					ft_strclr(buff);
				}
				write(1, "\n", 1);
			}
			else
			{
				write(1, ptr->name, ft_strlen(ptr->name));
				write(1, "\n", 1);
			}
		}
		ptr = ptr->next;
	}
	if (flags & LL_FLAG && !(flags & UC_FLAG))
		free(tmp);
	free(buff);
	times.timelimit++;
}

void		ft_putfilesdebug(t_file *head, int flags, t_times times)
{
	t_file	*ptr;
	char	*buff;
	char	*tmp;
	char	*p;
	char	lens[5];

	if (!(buff = (char *)ft_memalloc(sizeof(char) * 256)))
		return ;
	if (flags & LL_FLAG && !(flags & UC_FLAG))
	{
		ptr = head;
		while (ptr)
		{
			ptr->pw = getpwuid(ptr->filestat.st_uid);
			ptr->gr = getgrgid(ptr->filestat.st_gid);
			ptr->owner = ptr->pw->pw_name;
			ptr->group = ptr->gr->gr_name;
			ptr = ptr->next;
		}
		ft_getlens(head, &lens);
		lens[4] = 11 + lens[0] + lens[1] + lens[2] + lens[3] + 7 + 13;
		if (!(tmp = (char *)malloc(sizeof(char) * (lens[4] + 1))))
			return ;
		*(tmp + lens[4]) = '\0';
	}
	ptr = head;
	while (ptr)
	{
		if (flags & LL_FLAG && !(flags & UC_FLAG))
		{
			ft_memset(tmp, ' ', lens[4]);
			p = tmp;
			p += 11;
			ft_put_onwork_permissions(ptr->filestat.st_mode, p - 2);
			p += lens[0];
			ft_put_onwork_value(ptr->filestat.st_nlink, p);
			p += 2;
			ft_put_onwork_owner(ptr->pw, p);
			p += lens[1];
			p += 2;
			ft_put_onwork_group(ptr->gr, p);
			p += lens[2] + lens[3] + 1;
			ft_put_onwork_value(ptr->filestat.st_size, p);
			p += 2;
			ft_put_onwork_time(ptr->filestat, ptr->date, times, p);
			write(1, tmp, lens[4]);
			write(1, ptr->name, ft_strlen(ptr->name));
			if (S_ISLNK(ptr->filestat.st_mode))
			{
				write(1, " -> ", 4);
				readlink(ptr->path, buff, 256);
				write(1, buff, 256);
				ft_strclr(buff);
			}
			write(1, "\n", 1);
		}
		else
		{
			write(1, ptr->name, ft_strlen(ptr->name));
			write(1, "\n", 1);
		}
		ptr = ptr->next;
	}
	if (flags & LL_FLAG && !(flags & UC_FLAG))
		free(tmp);
	free(buff);
	times.timelimit++;
}

void		ft_put_permission_denied(char *path)
{
	char	*ptr;
	char	*p;

	write(1, "ls: ", 4);
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
	write(1, ptr, p - ptr);
	write(1, ": Permission denied\n", 20);
}

/*
	newf->name = path;
	newf->path = path;
	newf->owner = ft_get_owner(filestat);
	newf->group = ft_get_group(filestat);
	newf->date = filestat.st_mtime;
	newf->size = filestat.st_size;
	newf->permissions = ft_get_permissions(filestat);
	newf->hard_links = filestat.st_nlink;
	newf->next = NULL;
*/