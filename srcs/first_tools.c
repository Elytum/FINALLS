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
	newf->name = path;
	newf->path = path;
	newf->owner = ft_get_owner(filestat);
	newf->group = ft_get_group(filestat);
	newf->date = filestat.st_mtime;
	newf->size = filestat.st_size;
	newf->permissions = ft_get_permissions(filestat);
	newf->hard_links = filestat.st_nlink;
	newf->next = NULL;
	ft_insert_new_file(first, newf, f);
}

void			ft_add_new_file2(t_file **first, char *name,
								char *path, compare f)
{
	t_file		*newf;
	BYPASS		filestat;

	if ((stat(path, &filestat) == -1) ||
		!(newf = (t_file *)malloc(sizeof(t_file))))
		return ;
	newf->name = name;
	newf->path = ft_strdup(path);
	newf->owner = ft_get_owner(filestat);
	newf->group = ft_get_group(filestat);
	newf->date = filestat.st_mtime;
	newf->size = filestat.st_size;
	newf->permissions = ft_get_permissions(filestat);
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

void				ft_manage_directory(char *dir, compare f, char flags, int len)
{
	DIR				*dirp;
	struct dirent	*direntp;
	char			*path;
	char			**paths;
	char			*ptr;
	char			**pptr;
	t_file			*files;

	write(1, "\n", 1);
	write(1, dir, len);
	write(1, ":\n", 2);
	if (!(path = (char *)malloc(sizeof(char) * (256 + len))))
		return ;
	if (!(dirp = opendir(dir)))
	{
		ft_put_permission_denied(dir);
		return ;
	}
	ft_strcpy(path, dir);
	ptr = path + len;
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
			ft_strcpy(ptr, direntp->d_name);
			ft_add_new_file2(&files, direntp->d_name, path, f);
		}
	}
	free(path);
	ft_freefiles2(&files);
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
