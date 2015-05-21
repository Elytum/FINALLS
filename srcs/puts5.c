#include <ft_ls.h>

static void			ft_getlens_init(char lens[][7])
{
	(*lens)[0] = 0;
	(*lens)[1] = 0;
	(*lens)[2] = 0;
	(*lens)[3] = 0;
	(*lens)[4] = 0;
	(*lens)[5] = 0;
	(*lens)[6] = 0;
}

static void			begin_loop(char lens[][7], t_file *ptr)
{
	char			tmp;

	tmp = ft_intlen(ptr->filestat.st_nlink);
	if ((*lens)[0] < tmp)
		(*lens)[0] = tmp;
	tmp = ft_strlen(ptr->owner);
	if ((*lens)[1] < tmp)
		(*lens)[1] = tmp;
	tmp = ft_strlen(ptr->group);
	if ((*lens)[2] < tmp)
		(*lens)[2] = tmp;
	tmp = ft_intlen(ptr->filestat.st_size);
	if ((*lens)[3] < tmp)
		(*lens)[3] = tmp;
}

void				ft_getlens(t_file *head, char lens[][7])
{
	t_file			*ptr;
	char			tmp;

	ft_getlens_init(lens);
	ptr = head;
	while (ptr)
	{
		begin_loop(lens, ptr);
		if (S_ISCHR(ptr->filestat.st_mode) || S_ISBLK(ptr->filestat.st_mode))
		{
			ptr->major = ft_itoa(major(ptr->filestat.st_rdev));
			ptr->minor = ft_itoa(minor(ptr->filestat.st_rdev));
			tmp = ft_strlen(ptr->major);
			if ((*lens)[5] < tmp)
				(*lens)[5] = tmp;
			tmp = ft_strlen(ptr->minor);
			if ((*lens)[6] < tmp)
				(*lens)[6] = tmp;
		}
		else
		{
			ptr->major = NULL;
			ptr->minor = NULL;
		}
		ptr = ptr->next;
	}
}