#include "../includes/ft_ls.h"

int				ft_cmpname(t_file *s1, t_file *s2)
{
	return (ft_strcmp(s1->name, s2->name));
}

int				ft_cmprname(t_file *s1, t_file *s2)
{
	return (ft_strcmp(s2->name, s1->name));
}

int				ft_anyway(t_file *s1, t_file *s2)
{
	return (1);
	(void)s1;
	(void)s2;
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
	if (flags & LF_FLAG)
		return (&ft_anyway);
	if (flags & LR_FLAG)
		return (ft_get_function_reverse(flags));
	if (flags & LT_FLAG)
		return (&ft_cmpdate);
	if (flags & US_FLAG)
		return (&ft_cmpsize);
	return (&ft_cmpname);
}
