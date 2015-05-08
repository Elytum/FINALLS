#include "../includes/ft_ls.h"
#include <unistd.h>

static void		ft_insert_new_file(t_file **first, t_file *newf, compare f)
{
	t_file		*ptr;

	if (!*first)
		*first = newf;
	else if (f(newf, *first) < 0)
	{
		newf->next = *first;
		*first = newf;
	}
	else
	{
		ptr = *first;
		while (ptr->next && f(newf, ptr->next) > 0)
			ptr = ptr->next;
		newf->next = ptr->next;
		ptr->next = newf;
	}
}

static void		ft_add_new_file(t_file **first, char *path,
					BYPASS filestat, compare f)
{
	t_file		*newf;

	if (!(newf = (t_file *)malloc(sizeof(t_file))))
		return ;
/**/newf->name = path;
/**/newf->path = path;
	newf->filestat = filestat;
	newf->date = filestat.st_mtime;
	newf->next = NULL;
	ft_insert_new_file(first, newf, f);
}

void			ft_add_new_file2(t_file **first, t_info info, compare f, int flags)
{
	t_file		*newf;
	BYPASS		filestat;

	if ((lstat(info.path, &filestat) == -1) ||
		!(newf = (t_file *)malloc(sizeof(t_file))))
		return ;
	newf->name = ft_strdup(info.name);
	newf->path = ft_strdup(info.path);
	newf->filestat = filestat;
	newf->date = filestat.st_mtime;
	newf->next = NULL;
	ft_insert_new_file(first, newf, f);
}

void				ft_split_order_type(t_paths *paths,
					t_file **files, compare f)
{
	t_paths		*p;
	struct stat	statbuf;

	p = paths;
	while (p)
	{
		stat(p->path, &statbuf);
		ft_add_new_file(files, p->path, statbuf, f);
		p = p->next;
	}
}

void				ft_puttotal(t_file *files)
{
	t_file			*ptr;
	size_t			total;

	total = 0;
	ptr = files;
	if (!files)
		return ;
	while (ptr)
	{
		total += ptr->filestat.st_blocks;
		ptr = ptr->next;
	}
	write(1, "total ", 6);
	ft_putsize_t(total);
	write(1, "\n", 1);
}

void				ft_manage_directory(char *dir, compare f, int flags, t_times times)
{
	DIR				*dirp;
	struct dirent	*direntp;
	char			**paths;
	char			*ptr;
	char			**pptr;
	t_file			*files;
	t_info			info;
	int				len;

	len = ft_strlen(dir);
	if (!(flags & SINGLE))
	{
		if (flags & FIRST)
			flags &= ~FIRST;
		else
			write(1, "\n", 1);
		write(1, dir, len);
		write(1, ":\n", 2);
	}
	else
		flags &= ~SINGLE;
	if (!(info.path = (char *)malloc(sizeof(char) * (256 + len))))
		return ;
	if (!(dirp = opendir(dir)))
	{
		ft_put_permission_denied(dir);
		return ;
	}
	ft_strcpy(info.path, dir);
	ptr = info.path + len;
	*ptr++ = '/';
	*ptr = '\0';
	files = NULL;
	paths = NULL;
	while ((direntp = readdir(dirp)))
	{
		if (direntp == NULL)
			break ;
		if (flags & LA_FLAG || direntp->d_name[0] != '.')
		{
			info.name = direntp->d_name;
			ft_strcpy(ptr, direntp->d_name);
			ft_add_new_file2(&files, info, f, flags);
		}
	}
	closedir(dirp);
	if (flags & LL_FLAG)
		ft_puttotal(files);
	ft_putfilesdebug(files, flags, times);
	paths = ft_extractpaths(files);
	free(info.path);
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
