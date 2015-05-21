#include "../includes/ft_ls.h"
#include <unistd.h>

static void	first_step(t_file *ptr)
{
	write(1, ptr->name, ft_strlen(ptr->name));
	if (ptr->next)
		write(1, ", ", 2);
	else
		write(1, "\n", 1);
}



static void	last_step(t_file *ptr, int flags)
{
	int		len;

	len = ft_strlen(ptr->name);
	write(1, ptr->name, len);
	ft_put_after(ptr, flags);
	write(1, "\n", 1);
}

static void	ft_frees(int flags, char *buff, char *tmp)
{
	if (flags & LL_FLAG && !(flags & UC_FLAG))
		free(tmp);
	free(buff);
}

static void	ft_bigbadassloop(int flags, t_file *ptr, t_times times, char lens[7])
{
	char	*tmp;
	char	*buff;
	char	*p;

	if (!(buff = (char *)ft_memalloc(sizeof(char) * 256)))
		return ;
	if (flags & LL_FLAG && !(flags & UC_FLAG))
	{
		if (!((tmp = (char *)malloc(sizeof(char) * (lens[4] + 1)))))
			return ;
		*(tmp + lens[4]) = '\0';
	}
	while (ptr)
	{
		if (flags & LM_FLAG)
			first_step(ptr);
		else if (flags & LL_FLAG && !(flags & UC_FLAG))
			second_step_1(&tmp, &p, lens, ptr),
			ft_put_onwork_time(ptr->filestat, ptr->date, times, p),
			write(1, tmp, lens[4]), second_step_2(flags, buff, ptr);
		else
			last_step(ptr, flags);
		ptr = ptr->next;
	}
	ft_frees(flags, buff, tmp);
}

void		ft_putfilesdebug(t_file *head, int flags, t_times times)
{
	t_file	*ptr;
	char	*buff;
	char	*tmp;
	char	*p;
	char	lens[7];

	if (flags & LL_FLAG && !(flags & UC_FLAG))
	{
		ptr = head;
		while (ptr)
		{
			ptr->pw = getpwuid(ptr->filestat.st_uid);
			ptr->gr = getgrgid(ptr->filestat.st_gid);
			if (!ptr->pw || !(ptr->owner = ptr->pw->pw_name))
				ptr->owner = ft_itoa(ptr->filestat.st_uid);
			if (!ptr->gr || !(ptr->group = ptr->gr->gr_name))
				ptr->group = ft_itoa(ptr->filestat.st_gid);
			ptr = ptr->next;
		}
		ft_getlens(head, &lens);
		lens[4] = 11 + lens[0] + lens[1] + lens[2] + lens[3] + 7 + 13;
		if (lens[5] || lens[6])
			lens[4] += lens[5] + lens[6] + 2;
	}
	ft_bigbadassloop(flags, head, times, lens);
}
