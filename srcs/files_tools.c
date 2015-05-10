#include "../includes/ft_ls.h"

void		ft_insert_new_file(t_file **first, t_file *newf, compare f)
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
		if (lstat(p->path, &statbuf) == -1)
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