#include "../includes/ft_ls.h"

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

void			ft_add_new_file2(t_file **first, t_info info, compare f, char flags)
{
	t_file		*newf;
	BYPASS		filestat;

	if ((lstat(info.path, &filestat) == -1) ||
		!(newf = (t_file *)malloc(sizeof(t_file))))
		return ;
	newf->name = ft_strdup(info.name);
	newf->path = info.path;
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

void				ft_manage_directory(char *dir, compare f, char flags, t_times times)
{
	DIR				*dirp;
	struct dirent	*direntp;
	// char			*path;
	char			**paths;
	char			*ptr;
	char			**pptr;
	t_file			*files;
	t_info			info;
	int				len;

	len = ft_strlen(dir);
	write(1, "\n", 1);
	write(1, dir, len);
	write(1, ":\n", 2);
	if (!(info.path = (char *)malloc(sizeof(char) * (256 + len))))
		return ;
	if (!(dirp = opendir(dir)))
	{
		ft_put_permission_denied(dir);
		return ;
	}
	ft_strcpy(info.path, dir);
	ptr = info.path + len;
	if (*(ptr - 1) != '/')
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
	ft_putfilesdebug(files, flags, times);
	paths = ft_extractpaths(files);
	free(info.path);
	ft_freefiles2(&files, flags);
	if (flags & UR_FLAG && paths)
	{
		pptr = paths;
		while (*pptr)
		{
	// 		// dprintf(1, "*pptr = '%s'\n", *pptr);
			ft_manage_directory(*pptr, f, flags, times);
			free(*pptr++);
		}
	}
	free(paths);

	
					// ft_putfilesdebug(files, flags);
					// if (flags & UR_FLAG)
						// paths = ft_extractpaths(files);
// ft_freefiles(&files);
	// if (flags & UR_FLAG && paths)
	// {
	// 	pptr = paths;
	// 	while (*pptr)
	// 	{
	// 		// dprintf(1, "*pptr = '%s'\n", *pptr);
	// 		ft_manage_directory(*pptr, f, flags, ft_strlen(*pptr));
	// 		free(*pptr++);
	// 	}
	// }
	// if (flags & UR_FLAG && paths && (pptr = paths - 1))
						// while (*(++pptr))
							// ft_manage_directory(*pptr, f, flags, ft_strlen(*pptr));
	closedir(dirp);
}
