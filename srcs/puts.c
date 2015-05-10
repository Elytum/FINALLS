#include "../includes/ft_ls.h"
#include <unistd.h>
#define S_ISISVTX 0001000
#define S_ISUID   0004000
#define S_ISGID   0002000
#define XATTR_SIZE 10000
// #define	major(x)	((int32_t)(((u_int32_t)(x) >> 8) & 0xff))
// #define	minor(x)	((int32_t)((x) & 0xff) | (((x) & 0xffff0000) >> 8))

#include <sys/xattr.h>

int				ft_isnotlinktodir(char *path, int mode)
{
	struct stat	statbuf;
	char		*tmp;
	int			i;

	DIR		*dir;

	if (!S_ISLNK(mode))
		return (0);
	if ((dir = opendir(path)))
	{
		closedir(dir);
		return (0);
	}
	// else if (stat(path, &statbuf) == -1)
	// 	return (0);
	return (1);
}


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

void				ft_put_onwork_permissions(mode_t var, char *path, char *p)
{
	// dprintf(1, "p = %s, %zi\n", p, listxattr(p, NULL, 0, XATTR_NOFOLLOW));
	if (listxattr(p, NULL, 0, XATTR_NOFOLLOW) > 0)
		*path-- = '@';
	else
		path--;
	if (var & S_ISISVTX)
	{
		
		if (var & S_IWOTH || var & S_IROTH)
		{
			*path-- = 't';
			*path-- = ((var & S_IWOTH) ? 'w' : '-');
			*path-- = ((var & S_IROTH) ? 'r' : '-');
		}
		else
		{
			*path-- = 'T';
			*path-- = '-';
			*path-- = '-';
		}
	}
	else
	{
		*path-- = ((var & S_IXOTH) ? 'x' : '-');
		*path-- = ((var & S_IWOTH) ? 'w' : '-');
		*path-- = ((var & S_IROTH) ? 'r' : '-');
	}
	if (var & S_ISGID)
	{
		if (var & S_IXGRP || var & S_IXGRP)
		{
			*path-- = 's';
			*path-- = ((var & S_IWGRP) ? 'w' : '-');
			*path-- = ((var & S_IRGRP) ? 'r' : '-');
		}
		else
		{
			*path-- = 'S';
			*path-- = '-';
			*path-- = '-';
		}
	}
	else
	{
		*path-- = ((var & S_IXGRP) ? 'x' : '-');
		*path-- = ((var & S_IWGRP) ? 'w' : '-');
		*path-- = ((var & S_IRGRP) ? 'r' : '-');
	}
	if (var & S_ISUID)
	{
		if (var & S_IXUSR || var & S_IWUSR)
		{
			*path-- = 's';
			*path-- = ((var & S_IWUSR) ? 'w' : '-');
			*path-- = ((var & S_IRUSR) ? 'r' : '-');
		}
		else
		{
			*path-- = 'S';
			*path-- = '-';
			*path-- = '-';
		}
	}
	else
	{
		*path-- = ((var & S_IXUSR) ? 'x' : '-');
		*path-- = ((var & S_IWUSR) ? 'w' : '-');
		*path-- = ((var & S_IRUSR) ? 'r' : '-');
	}
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

void				ft_put_onwork_owner(char *name, char *path)
{
	if (!name)
		return ;
	ft_strcpyo(path, name);
}

void				ft_put_onwork_group(char *group, char *path)
{
	if (!group)
		return ;
	ft_strcpyo(path, group);
}

void				ft_put_onwork_time(BYPASS filestat, time_t date, t_times times, char *path)
{
	// dprintf (1, "date = %u, date > times.timelimit = %u, times.launchtime = %u\n", date, times.timelimit, times.launchtime);
	if (date > times.timelimit && date <= time(NULL))
		ft_strncpyo(path, ctime(&(filestat).st_mtime) + 4, 12);
	else
	{
		ft_strncpyo(path, ctime(&(filestat).st_mtime) + 4, 7);
		ft_strncpyo(path + 8, ctime(&(filestat).st_mtime) + 20, 4);
	}
	// write(1, " ", 1);
}

void				ft_getlens(t_file *head, char lens[][7])
{
	t_file			*ptr;
	char			tmp;

	(*lens)[0] = 0;
	(*lens)[1] = 0;
	(*lens)[2] = 0;
	(*lens)[3] = 0;
	(*lens)[4] = 0;
	(*lens)[5] = 0;
	(*lens)[6] = 0;
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
		if ((*lens)[3] < tmp)
			(*lens)[3] = tmp;
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

void		ft_put_devices(char *major, char *minor, int len, char *ptr)
{
	char	*p;

	p = minor;
	while (*p)
		p++;
	if (p != minor)
		p--;
	len -= (p - minor);
	while (p >= minor)
		*ptr-- = *p--;
	while (len--)
		ptr--;
	*ptr-- = ',';
	p = major;
	while (*p)
		p++;
	if (p != major)
		p--;
	while (p >= major)
		*ptr-- = *p--;
	// *ptr = 'a';
	// (void)major;
	// (void)minor;
	// (void)ptr;
}

void		ft_putfiles(t_file *head, int flags, t_times times)
{
	t_file	*ptr;
	char	*buff;
	char	*tmp;
	char	*p;
	char	lens[7];

	if (!(buff = (char *)ft_memalloc(sizeof(char) * 256)))
		return ;
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
		ft_getlens(head, &lens);//1 + 1 + 2 + 2 + 1
		lens[4] = 11 + lens[0] + lens[1] + lens[2] + lens[3] + 7 + 13;
		if (lens[5] || lens[6])
			lens[4] += lens[5] + lens[6] + 2;
		if (!(tmp = (char *)malloc(sizeof(char) * (lens[4]))))
			return ;
		*(tmp + lens[4]) = '\0';
	}
	ptr = head;
	while (ptr)
	{
		if (S_ISREG(ptr->filestat.st_mode) || (S_ISLNK(ptr->filestat.st_mode) && (flags & LL_FLAG)) || ft_isnotlinktodir(ptr->path, ptr->filestat.st_mode))
		{
			if (flags & LL_FLAG && !(flags & UC_FLAG))
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

				write(1, ptr->name, ft_strlen(ptr->name));
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
				write(1, ptr->name, ft_strlen(ptr->name));
				write(1, "\n", 1);
			}
		}
		ptr = ptr->next;
	}
	if (flags & LL_FLAG && !(flags & UC_FLAG))
		free(tmp);
	free(buff);
	// times.timelimit++;
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
		//check whiteout
		else if (S_ISFIFO(file->filestat.st_mode))
			write(1, "|", 1);
		else if (file->filestat.st_mode & S_IXUSR)
			write(1, "*", 1);
	}
	else if (flags & LP_FLAG)
		if (file->filestat.st_mode & S_IFDIR)
			write(1, "/", 1);
}

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
		// dprintf(1, "SIZE 2 : %i\n", lens[5]);
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
	// times.timelimit++;
}

void		ft_put_permission_denied(char *path)
{
	char	*ptr;
	char	*p;

	// write(1, "ls: ", 4);
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