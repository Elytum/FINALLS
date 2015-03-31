#include "../includes/ft_ls.h"

int				ft_cmpname(t_file *s1, t_file *s2)
{
	return (ft_strcmp(s1->name, s2->name));
}

int				ft_cmprname(t_file *s1, t_file *s2)
{
	return (ft_strcmp(s2->name, s1->name));
}

int				ft_cmpdate(t_file *s1, t_file *s2)
{
	int			ret;

	ret = s2->filestat.st_mtime - s1->filestat.st_mtime;
	if (!ret)
		ret = ft_strcmp(s1->name, s2->name);
	return (ret);
}

int				ft_cmprdate(t_file *s1, t_file *s2)
{
	int			ret;

	ret = s1->filestat.st_mtime - s2->filestat.st_mtime;
	if (!ret)
		ret = ft_strcmp(s2->name, s1->name);
	return (ret);
}

int				ft_cmpsize(t_file *s1, t_file *s2)
{
	int			ret;

	if (!(ret = s2->filestat.st_size - s1->filestat.st_size))
		ret = ft_strcmp(s1->name, s2->name);
	return (ret);
}

int				ft_cmprsize(t_file *s1, t_file *s2)
{
	int			ret;

	if (!(ret = s1->filestat.st_size - s2->filestat.st_size))
		ret = ft_strcmp(s2->name, s1->name);
	return (ret);
}

static compare	ft_get_function_reverse(int flags)
{
	if (flags & LT_FLAG)
		return (&ft_cmprdate);
	if (flags & US_FLAG)
		return (&ft_cmprsize);
	return (&ft_cmprname);
}

compare			ft_get_function(int flags)
{
	if (flags & LR_FLAG)
		return (ft_get_function_reverse(flags));
	if (flags & LT_FLAG)
		return (&ft_cmpdate);
	if (flags & US_FLAG)
		return (&ft_cmpsize);
	return (&ft_cmpname);
}
