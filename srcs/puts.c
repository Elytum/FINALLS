#include "../includes/ft_ls.h"
#include <unistd.h>

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
