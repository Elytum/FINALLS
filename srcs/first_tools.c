#include "../includes/ft_ls.h"
#include <unistd.h>

DIR					*ft_directory_intro(char *dir, int *flags, int *len, t_info *info)
{
	DIR				*dirp;

	*len = ft_strlen(dir);
	if (*flags & FIRST)
		*flags &= ~FIRST;
	else
		write(1, "\n", 1);
	
	if (!(*flags & SINGLE))
	{
		write(1, dir, *len);
		write(1, ":\n", 2);
	}
	else
		*flags &= ~SINGLE;
	if (!(info->path = (char *)malloc(sizeof(char) * (256 + *len))))
		return (NULL);
	if (!(dirp = opendir(dir)))
	{
		ft_put_permission_denied(dir);
		return (NULL);
	}
	return (dirp);
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

	if (!(dirp = ft_directory_intro(dir, &flags, &len, &info)))
		return ;
	
	
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
