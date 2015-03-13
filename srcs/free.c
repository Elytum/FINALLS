#include "../includes/ft_ls.h"

void		ft_freefiles(t_file **head)
{
	t_file	*ptr;
	t_file	*past;

	ptr = *head;
	while (ptr)
	{
		free(ptr->permissions);
		free(ptr->owner);
		free(ptr->group);
		free(ptr->name);
		// free(ptr->path);
		// ptr->path = NULL;
		free(ptr->phard_links);
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
		// free(ptr->permissions);
		// free(ptr->hard_links);
		// free(ptr->owner);
		// free(ptr->group);
		// // free(ptr->name);
		// // free(ptr->path);
		// free(ptr->psize);
		// free(ptr->pdate);


	free(ptr->owner);
	free(ptr->group);
	free(ptr->pdate);
	// ptr->size = filestat.st_size;
	free(ptr->psize);
	// ptr->psize = NULL;
	free(ptr->permissions);
	free(ptr->phard_links);

		past = ptr;
		ptr = ptr->next;
		free(past);
	}
}

void		ft_freefiles2(t_file **head)
{
	t_file	*ptr;
	t_file	*past;

	ptr = *head;
	while (ptr)
	{
		//newf->name = name;
		free(ptr->path);// = ft_strdup(path);
		free(ptr->owner);// = ft_get_owner(filestat);
		free(ptr->group);// = ft_get_group(filestat);
		free(ptr->permissions);// = ft_get_permissions(filestat);
		past = ptr;
		ptr = ptr->next;
		free(past);
	}
}