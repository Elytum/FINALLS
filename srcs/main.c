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

//-l -R -a -r -t
#define l_FLAG 0b00000001
#define R_FLAG 0b00000010
#define a_FLAG 0b00000100
#define r_FLAG 0b00001000
#define t_FLAG 0b00010000
#define ERROR 0b10000000
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

typedef struct		s_paths
{
	char			*path;
	struct s_paths	*next;
}					t_paths;

// typedef struct		s_file
// {
// 	int				date;
// 	char			*permissions;
// 	char			*hard_links;
// 	char			*owner;
// 	char			*group;
// 	char			*size;
// 	char			*date;
// 	char			*name;
// 	char			*path;
// 	struct s_file	*nextfile;
// }					t_file;

size_t			ft_strlen(char *str)
{
	char		*ptr;

	ptr = str;
	while (*ptr)
		ptr++;
	return (ptr - str);
}

char				*ft_strdup(char *str)
{
	register char	*strnew;
	register char	*ptr;

	if (!(strnew = (char *)malloc(sizeof(char) * ft_strlen(str) + 1)))
		return (NULL);
	ptr = strnew;
	while (*str)
		*ptr++ = *str++;
	*ptr = '\0';
	return (strnew);
}

void			ft_fillflag(char p, char *flags)
{
	if (p == 'l')
		(*flags) |= l_FLAG;
	else if (p == 'R')
		(*flags) |= R_FLAG;
	else if (p == 'a')
		(*flags) |= a_FLAG;
	else if (p == 'r')
		(*flags) |= r_FLAG;
	else if (p == 't')
		(*flags) |= t_FLAG;
	else
	{
		write (1, "ls: illegal option -- ", 22);
		write (1, &p, 1);
		write (1, "\nusage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n", 63);
		(*flags) |= ERROR;
	}
}

char			ft_getflags(char ***str)
{
	char		flags;
	char		*p;

	flags = 0;
	(*str)++;
	while (*(*str))
	{
		if (**(*str) != '-')
			return (flags);
		if ((**(*str) == '-' && *(*(*str) + 1) == '-'))
		{
			// dprintf(1, "Test = '%s'\n", (**str + 2));
			if (*(*(*str) + 2))
			{
				write (1, "ls: illegal option -- -\nusage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n", 87);
				flags |= ERROR;
			}
			(*str)++;
			return (flags);
		}
		p = *(*str) + 1;
		while (*p)
		{
			ft_fillflag(*p, &flags);
			if (flags & ERROR)
				return (flags);
			p++;
		}
		(*str)++;
	}
	return (flags);
}

void			ft_testflags(char flags)
{
	if (flags & l_FLAG)
		dprintf(1, "l_Flag detected\n");
	if (flags & R_FLAG)
		dprintf(1, "R_Flag detected\n");
	if (flags & a_FLAG)
		dprintf(1, "a_Flag detected\n");
	if (flags & r_FLAG)
		dprintf(1, "r_Flag detected\n");
	if (flags & t_FLAG)
		dprintf(1, "t_Flag detected\n");
}

void			ft_putfiles(char **av)
{
	char		**ptr;

	ptr = av;
	while (*ptr)
	{
		write(1, *ptr, ft_strlen(*ptr));
		write(1, "\n", 1);
		ptr++;
	}
}

// void			ft_addpath(t_paths **paths, char *path, int	(*f)(const char *, const char *))
// {
// 	(void)paths;
// 	(void)path;
// 	(void)f;
// }

int				ft_strcmp(const char *s1, const char *s2)
{
	if (!s1)
		return ((unsigned char)*s2);
	if (!s2)
		return ((unsigned char)*s1);
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

// int 			(*ft_getfunction(char flags))(const char *, const char *)
void			ft_setfunction(int (**f)(const char *, const char *), char flags)
{
	*f = &ft_strcmp;
	(void)flags;
	(void)f;
}

/*

ft_condense :
On a liste chainee de pleins de valeurs, probablement des trucs mallocés
On a trié grâce à fileadd et function
On a donc l'ordre valide
On peut donc juste garder le path

*/

/*
typedef struct		s_paths
{
	char			*path;
	struct s_paths	*next;
}					t_paths;
*/

// a + b
// a b c e f + d

void			ft_addpath(t_paths **paths, char *p)
{
	t_paths		*ptr;
	t_paths		*newp;

	if (!(newp = (t_paths *)malloc(sizeof(t_paths))))
		return ;
	newp->path = ft_strdup(p);
	newp->next = NULL;
	if (!*paths)
		*paths = newp;
	else if (ft_strcmp(p, (*paths)->path) < 0)
	{
		newp->next = *paths;
		*paths = newp;
	}
	else
	{
		ptr = *paths;
		while (ptr->next && ft_strcmp(p, ptr->next->path) > 0)
			ptr = ptr->next;
		newp->next = ptr->next;
		ptr->next = newp;
	}
}

void				ft_putpath(t_paths *paths)
{
	t_paths			*ptr;
	struct stat		statbuf;

	ptr = paths;
	while (ptr)
	{
		stat(ptr->path, &statbuf);
		if (S_ISREG(statbuf.st_mode))
			dprintf(1, "%s is a file\n", ptr->path);
		else if (S_ISDIR(statbuf.st_mode))
			dprintf(1, "%s is a directory\n", ptr->path);
		ptr = ptr->next;
	}
}

void				ft_cleanpath(t_paths **paths)
{
	t_paths			*ptr;
	t_paths			*past;
	struct stat		statbuf;

	ptr = *paths;
	past = NULL;
	while (ptr)
	{
		if (stat(ptr->path, &statbuf) == -1)
		{
			write(1, "ls: ", 4), write(1, ptr->path, ft_strlen(ptr->path));
			write(1, ": No such file or directory\n", 28);
			free(ptr->path), free(ptr);
			if (!past)
				*paths = (*paths)->next,
				ptr = (*paths);
			else
				past->next = past->next->next,
				ptr = past->next;
		}
		else
			past = ptr,
			ptr = ptr->next;
	}
}

void			ft_manage_first(char **args, char flags)
{
	// t_files		*files;
	// t_files		*direct;
	t_paths			*paths;
	// struct stat		statbuf;
	char			**ptr;
	int				(*function)(const char *, const char *);

	ft_setfunction(&function, flags);
	// dprintf(1, "Test = %i\n", function("abc", "def"));

	paths = NULL;
	ptr = args;
	while (*ptr)
	{


		ft_addpath(&paths, *ptr);
		// On ajoute tout (avec tous les critères pour les tris)
		// On affiche les fichiers

		//#ft_condense(directories);
		//#ft_putfiles(files);
		//#if (flags & R_FLAG)
		//#ft_recursif(directories);
			// ft_addpath(&paths, *ptr, function);//dprintf(1, "Directory %s is a file\n", *ptr);
		ptr++;
	}
	ft_cleanpath(&paths);
	ft_putpath(paths);
}

int				main(int ac, char **av)
{
	char		flags;

	flags = 0;
	if (ac <= 1)
		return (0);
	if ((flags = ft_getflags(&av)) & ERROR)
	{
		// dprintf(1, "Error\n");
		return (0);
	}
	ft_testflags(flags);
	ft_manage_first(av, flags);

	return (0);
}