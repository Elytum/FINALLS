#include "../includes/ft_ls.h"

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
		// ptr->path = NULL;
		free(ptr->psize);
		free(ptr->pdate);
		past = ptr;
		ptr = ptr->next;
		free(past);
	}
}

void		ft_freefilestest(t_file **head)
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
		// free(ptr->name);
		// free(ptr->path);
		free(ptr->psize);
		free(ptr->pdate);
		past = ptr;
		ptr = ptr->next;
		free(past);
	}
}