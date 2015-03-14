#include "../includes/ft_ls.h"
#include <unistd.h>

void				ft_put_onwork_symbole(mode_t var)
{
	if (S_ISLNK(var))
		write(1, "l", 1);
	else if ((var & 0170000) == 0040000)
		write(1, "d", 1);
	else if ((var & 0170000) == 0020000)
		write(1, "c", 1);
	else if ((var & 0170000) == 0060000)
		write(1, "b", 1);
	else if ((var & 0170000) == 0010000)
		write(1, "p", 1);
	else if ((var & 0170000) == 0140000)
		write(1, "s", 1);
	write(1, "-", 1);
}

void				ft_put_onwork_permissions(mode_t var)
{
	ft_put_onwork_symbole(var);
	write(1, ((var & S_IRUSR) ? "r" : "-"), 1);
	write(1, ((var & S_IWUSR) ? "w" : "-"), 1);
	write(1, ((var & S_IXUSR) ? "x" : "-"), 1);
	write(1, ((var & S_IRGRP) ? "r" : "-"), 1);
	write(1, ((var & S_IWGRP) ? "w" : "-"), 1);
	write(1, ((var & S_IXGRP) ? "x" : "-"), 1);
	write(1, ((var & S_IROTH) ? "r" : "-"), 1);
	write(1, ((var & S_IWOTH) ? "w" : "-"), 1);
	write(1, ((var & S_IXOTH) ? "x" : "-"), 1);
	write(1, "  ", 2);
}

void				ft_put_onwork_value_loop(int n)
{
	char			c;

	if (n >= 10)
	{
		ft_put_onwork_value_loop(n / 10);
		c = n % 10 + '0';
		write(1, &c, 1);
	}
	else
	{
		c = n + '0';
		write(1, &c, 1);
	}
}

void				ft_put_onwork_value(int n)
{
	if (n == -2147483648)
		write(1, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(1, "-", 1);
			n = -n;
		}
		ft_put_onwork_value_loop(n);
	}
}

void				ft_put_onwork_owner(int uid)
{
	struct passwd	*pw;

	if (!(pw = getpwuid(uid)))
		return ;
	write(1, pw->pw_name, ft_strlen(pw->pw_name));
	write(1, " ", 1);
}

void				ft_put_onwork_group(int gid)
{
	struct group	*gr;

	if (!(gr = getgrgid(gid)))
		return ;
	write(1, gr->gr_name, ft_strlen(gr->gr_name));
	write(1, " ", 1);
}

void		ft_put_onwork_time(BYPASS filestat, int date, t_times times)
{
	if (date > times.timelimit && date < times.launchtime)
		write(1, ctime(&(filestat).st_mtime) + 4, 12);
	else
	{
		write(1, ctime(&(filestat).st_mtime) + 4, 7);
		write(1, " ", 1);
		write(1, ctime(&(filestat).st_mtime) + 20, 4);
	}
	write(1, " ", 1);
}

void		ft_putfilesdebug(t_file *head, char flags, t_times times)
{
	t_file	*ptr;
	char	*buff;

	if (!(buff = (char *)ft_memalloc(sizeof(char) * 256)))
		return ;
	ptr = head;
	while (ptr)
	{
		// dprintf(1, "Name : %s\n", ptr->name);
		if (0 && flags & LL_FLAG)
		{
			ft_put_onwork_permissions(ptr->filestat.st_mode);
			ft_put_onwork_value(ptr->filestat.st_nlink);
			write(1, " ", 1);
			ft_put_onwork_owner(ptr->filestat.st_gid);
			ft_put_onwork_group(ptr->filestat.st_uid);
			ft_put_onwork_value(ptr->filestat.st_size);
			write(1, " ", 1);
			write(1, " ", 1);
			ft_put_onwork_time(ptr->filestat, ptr->date, times);
			write(1, ptr->name, ft_strlen(ptr->name));
			if (S_ISLNK(ptr->filestat.st_mode))
			{
				write(1, " -> ", 4);
				readlink(ptr->path, buff, 256);
				write(1, buff, 256);
				ft_strclr(buff);
			}
		}
		else
			write(1, ptr->name, ft_strlen(ptr->name));
		write(1, "\n", 1);
		// write(1, "LOL\n", 4);
		ptr = ptr->next;
	}
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