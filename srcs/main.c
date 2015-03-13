/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getflags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 04:49:41 by achazal           #+#    #+#             */
/*   Updated: 2014/11/25 22:54:45 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>
#define BYPASS struct stat

typedef int (*compare)(t_file *f1, t_file *f2);

void		ft_putfiles(char **av)
{
	char	**ptr;

	ptr = av;
	while (*ptr)
	{
		write(1, *ptr, ft_strlen(*ptr));
		write(1, "\n", 1);
		ptr++;
	}
}

char				ft_getsymbole(struct stat filestat)
{
	if ((filestat.st_mode & 0170000) == 0040000)
		return ('d');
	if ((filestat.st_mode & 0170000) == 0120000)
		return ('l');
	if ((filestat.st_mode & 0170000) == 0020000)
		return ('c');
	if ((filestat.st_mode & 0170000) == 0060000)
		return ('b');
	if ((filestat.st_mode & 0170000) == 0010000)
		return ('p');
	if ((filestat.st_mode & 0170000) == 0140000)
		return ('s');
	return ('-');
}

char		*ft_get_permissions(struct stat filestat)
{
	char	*permissions;

	permissions = (char *)malloc(sizeof(char) * (10 + 1));
	permissions[0] = ft_getsymbole(filestat);
	permissions[1] = ((filestat.st_mode & S_IRUSR) ? 'r' : '-');
	permissions[2] = ((filestat.st_mode & S_IWUSR) ? 'w' : '-');
	permissions[3] = ((filestat.st_mode & S_IXUSR) ? 'x' : '-');
	permissions[4] = ((filestat.st_mode & S_IRGRP) ? 'r' : '-');
	permissions[5] = ((filestat.st_mode & S_IWGRP) ? 'w' : '-');
	permissions[6] = ((filestat.st_mode & S_IXGRP) ? 'x' : '-');
	permissions[7] = ((filestat.st_mode & S_IROTH) ? 'r' : '-');
	permissions[8] = ((filestat.st_mode & S_IWOTH) ? 'w' : '-');
	permissions[9] = ((filestat.st_mode & S_IXOTH) ? 'x' : '-');
	permissions[10] = '\0';
	return (permissions);
}

char				*ft_get_owner(struct stat filestat)
{
	struct passwd	*pw;
	char			*str;

	pw = getpwuid(filestat.st_uid);
	if (!pw)
		str = NULL;
	else
		str = ft_strdup(pw->pw_name);
	return (str);
}

char				*ft_get_group(struct stat filestat)
{
	struct group	*gr;
	char			*str;

	gr = getgrgid(filestat.st_gid);
	if (!gr)
		str = NULL;
	else
		str = ft_strdup(gr->gr_name);
	return (str);
}

void				ft_insert_new_file(t_file **first, t_file *newf, compare f)
{
	t_file			*ptr;

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
	(void)ptr;
	// f(NULL, NULL);
}

void		ft_add_new_file(t_file **first, char *path, BYPASS filestat, compare f)
{
	t_file	*newf;

	if (!(newf = (t_file *)malloc(sizeof(t_file))))
		return ;
	newf->name = ft_strdup(path);
	newf->owner = ft_get_owner(filestat);
	newf->group = ft_get_group(filestat);
	newf->pdate = ft_strndup(ctime(&filestat.st_mtime) + 4, 12);
	newf->date = ft_atoi(newf->pdate);
	newf->size = filestat.st_size;
	newf->psize = ft_itoa(filestat.st_size);
	newf->permissions = ft_get_permissions(filestat);
	newf->hard_links = ft_itoa(filestat.st_nlink);
	newf->next = NULL;
	ft_insert_new_file(first, newf, f);
	// f(NULL, NULL);
}

void		ft_add_new_file2(t_file **first, char *name, char *path, compare f)
{
	t_file	*newf;
	BYPASS	filestat;

	if ((stat(path, &filestat) == -1) ||
		!(newf = (t_file *)malloc(sizeof(t_file))))
		return ;
	newf->name = ft_strdup(name);
	newf->path = ft_strdup(path);
	newf->owner = ft_get_owner(filestat);
	newf->group = ft_get_group(filestat);
	newf->pdate = ft_strndup(ctime(&filestat.st_mtime) + 4, 13);
	newf->date = ft_atoi(newf->pdate);
	newf->size = filestat.st_size;
	newf->psize = ft_itoa(filestat.st_size);
	newf->permissions = ft_get_permissions(filestat);
	newf->hard_links = ft_itoa(filestat.st_nlink);
	newf->next = NULL;
	ft_insert_new_file(first, newf, f);
	// f(NULL, NULL);
}


/*
** one ne remplit pas la liste de files avec le nom des dossiers
** la non one le fera, elle.
*/

int			ft_cmpname(t_file *s1, t_file *s2)
{
	return (ft_strcmp(s1->name, s2->name));
}

int			ft_cmprname(t_file *s1, t_file *s2)
{
	return (ft_strcmp(s2->name, s1->name));
}

int			ft_cmpdate(t_file *s1, t_file *s2)
{
	return (s1->date - s2->date);
}

int			ft_cmprdate(t_file *s1, t_file *s2)
{
	return (s2->date - s1->date);
}

compare		ft_get_function(char flags)
{
	if (!(flags & LR_FLAG) && !(flags & LT_FLAG))
		return (&ft_cmpname);
	if (!(flags & LT_FLAG))
		return (&ft_cmprname);
	if (!(flags & LR_FLAG))
		return (&ft_cmpdate);
	return (&ft_cmprdate);
	(void)flags;
}

void		ft_split_order_type_one(t_paths *paths, t_file **files,
									t_file **dirs, compare f)
{
	t_paths			*p;
	struct stat		statbuf;

	p = paths;
	while (p)
	{
		stat(p->path, &statbuf);
		if (S_ISREG(statbuf.st_mode))
			ft_add_new_file(files, p->path, statbuf, f);
		else if (S_ISDIR(statbuf.st_mode))
			ft_add_new_file(dirs, p->path, statbuf, f);
		p = p->next;
	}
}

void		ft_split_order_type_two(t_paths *paths, t_file **files,
									t_file **dirs, compare f)
{
	t_paths			*p;
	struct stat		statbuf;

	p = paths;
	while (p)
	{
		stat(p->path, &statbuf);
		ft_add_new_file(files, p->path, statbuf, f);
		if (S_ISDIR(statbuf.st_mode))
			ft_add_new_file(dirs, p->path, statbuf, f);
		p = p->next;
	}
}

void		ft_putfilesdebug(t_file *head, char flags)
{
	t_file	*ptr;

	ptr = head;
	while (ptr)
	{
		if (flags & LL_FLAG)
		{
			write(1, ptr->permissions, ft_strlen(ptr->permissions));
			write(1, " ", 1);
			write(1, ptr->hard_links, ft_strlen(ptr->hard_links));
			write(1, " ", 1);
			write(1, ptr->owner, ft_strlen(ptr->owner));
			write(1, " ", 1);
			write(1, ptr->group, ft_strlen(ptr->group));
			write(1, " ", 1);
			write(1, ptr->psize, ft_strlen(ptr->psize));
			write(1, " ", 1);
			write(1, ptr->pdate, ft_strlen(ptr->pdate));
			write(1, " ", 1);
		}
		write(1, ptr->name, ft_strlen(ptr->name));
		write(1, "\n", 1);
		ptr = ptr->next;
	}
}

char		**ft_extractpaths(t_file *head)
{
	int 	len;
	t_file	*ptr;
	char	**paths;
	char	**p;

	len = 0;
	ptr = head;
	while (ptr && ++len)
		ptr = ptr->next;
	if (!(paths = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	p = paths;
	ptr = head;
	while (ptr)
	{
		*p++ = ft_strdup(ptr->name);
		ptr = ptr->next;
	}
	*p = NULL;
	return (paths);
}

void		ft_freefiles(t_file **head)
{
	t_file	*ptr;
	t_file	*past;

	ptr = *head;
	while (ptr)
	{
		free(ptr->permissions);
		free(ptr->hard_links);
		free(ptr->owner);
		free(ptr->group);
		free(ptr->name);
		// free(ptr->path);
		free(ptr->psize);
		free(ptr->pdate);
		past = ptr;
		ptr = ptr->next;
		free(past);
	}
}

/*
char		**ft_extractpaths2(t_file *head)
{
	int 	len;
	t_file	*ptr;
	char	**paths;
	char	**p;

	len = 0;
	ptr = head;
	while (ptr)
	{
		if (ptr->permissions[0] == 'd' &&
			!((ptr->name[0] == '.' && !(ptr->name[1])) ||
			(ptr->name[0] == '.' && ptr->name[1] == '.' && !ptr->name[2])))
			len++;
		ptr = ptr->next;
	}
	if (!(paths = (char **)malloc(sizeof(len + 1))))
		return (NULL);
	p = paths;
	ptr = head;
	while (ptr)
	{
		if (ptr->permissions[0] == 'd' &&
			!((ptr->name[0] == '.' && !(ptr->name[1])) ||
			(ptr->name[0] == '.' && ptr->name[1] == '.' && !ptr->name[2])))
			*p++ = ft_strdup(ptr->path);
		ptr = ptr->next;
	}
	*p = NULL;
	return (paths);
*/

void		ft_freefiles2(t_file **head)
{
	t_file	*ptr;
	t_file	*past;

	ptr = *head;
	while (ptr)
	{
		free(ptr->permissions);
		free(ptr->hard_links);
		free(ptr->owner);
		free(ptr->group);
		free(ptr->name);
		free(ptr->path);
		free(ptr->psize);
		free(ptr->pdate);
		past = ptr;
		ptr = ptr->next;
		free(past);
	}
}

char		**ft_extractpaths2(t_file *head)
{
	int 	len;
	t_file	*ptr;
	char	**paths;
	char	**p;

	len = 0;
	ptr = head;
	while (ptr)
	{
		if (ptr->permissions[0] == 'd' &&
			!((ptr->name[0] == '.' && !(ptr->name[1])) ||
			(ptr->name[0] == '.' && ptr->name[1] == '.' && !ptr->name[2])))
			len++;
		ptr = ptr->next;
	}
	if (!(paths = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	p = paths;
	ptr = head;
	while (ptr)
	{
		if (ptr->permissions[0] == 'd' &&
			!((ptr->name[0] == '.' && !(ptr->name[1])) ||
			(ptr->name[0] == '.' && ptr->name[1] == '.' && !ptr->name[2])))
			*p++ = ft_strdup(ptr->path);
		ptr = ptr->next;
	}
	*p = NULL;
	return (paths);
	// }
	// if (!(paths = (char **)malloc(sizeof(char *) * (len + 1))))
	// 	return (NULL);
	// p = paths;
	// ptr = head;
	// while (ptr)
	// {
	// 	*p++ = ft_strdup(ptr->name);
	// 	ptr = ptr->next;
	// }
	// *p = NULL;
	// return (paths);
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

void		ft_manage_directory(char *dir, compare f, char flags, int len)
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
	if (!(path = (char *)malloc(sizeof(char) * (2567 + len))))
		return ;
	if (!(dirp = opendir(dir)))
	{
		ft_put_permission_denied(dir);
//		dprintf(1, "ls: a: Permission denied\n");
		return ;
	}
	ft_strcpy(path, dir);
	ptr = path + len;
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
	ft_putfilesdebug(files, flags);
	if (flags & UR_FLAG)
		paths = ft_extractpaths2(files);
	if (flags & UR_FLAG && paths && (pptr = paths - 1))
		while (*(++pptr))
			ft_manage_directory(*pptr, f, flags, ft_strlen(*pptr));
	closedir(dirp);
}

void		ft_manage_first(char **args, char flags)
{
	t_paths	*paths;
	char	**ptr;
	char	**p;
	t_file	*files;
	t_file	*dirs;
	compare	f;

	f = ft_get_function(flags);
	paths = NULL;
	files = NULL;
	dirs = NULL;
	ptr = args;
	while (*ptr)
	{
		ft_addpath(&paths, *ptr);
		ptr++;
	}
	ft_cleanpath(&paths);
	ft_split_order_type_one(paths, &files, &dirs, f);
	ft_putfilesdebug(files, flags);
	ptr = ft_extractpaths(dirs);
	ft_freefiles(&files);
	ft_freefiles(&dirs);
	p = ptr;
	// if (*p)
		// write(1, "\n", 1);
	while (*p)
	{
		// write(1, *p, ft_strlen(*p));
		// write(1, ":\n", 2);
		ft_manage_directory(*p, f, flags, ft_strlen(*p));
		free(*p);
		p++;
		// if (*p)
		// 	write(1, "\n", 1);
	}
	free(ptr);
}

int			main(int ac, char **av)
{
	char	flags;

	flags = 0;
	av++;
	if (ac > 1 && (flags = ft_getflags(&av)) & ERROR)
		return (0);
	if (!*av)
	{
		av = (char **)malloc(sizeof(char *) * 2);
		*av = ft_strdup(".");
		*(av + 1) = NULL;
	}
	ft_manage_first(av, flags);
	return (0);
}
