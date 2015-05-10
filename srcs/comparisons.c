#include "../includes/ft_ls.h"

int					ft_cmpname(t_file *s1, t_file *s2)
{
	return (ft_strcmp(s1->name, s2->name));
}

int					ft_cmprname(t_file *s1, t_file *s2)
{
	return (ft_strcmp(s2->name, s1->name));
}


static compare		ft_get_function_reverse(int flags)
{
	if (flags & LT_FLAG)
		return (&ft_cmprdate);
	if (flags & US_FLAG)
		return (&ft_cmprsize);
	return (&ft_cmprname);
}

compare		ft_get_singfunction(compare newp)
{
	static compare	ptr = NULL;

	if (newp)
		ptr = newp;
	return (ptr);
}

compare				ft_get_function(int flags)
{
	if (flags & LF_FLAG)
	{
		ft_get_singfunction(&ft_anyway);
		return (&ft_anyway);
	}
	if (flags & LR_FLAG)
	{
		ft_get_singfunction(ft_get_function_reverse(flags));
		return (ft_get_function_reverse(flags));
	}
	if (flags & LT_FLAG)
	{
		ft_get_singfunction(&ft_cmpdate);
		return (&ft_cmpdate);
	}
	if (flags & US_FLAG)
	{
		ft_get_singfunction(&ft_anyway);
		return (&ft_cmpsize);
	}
	return (&ft_cmpname);
}
