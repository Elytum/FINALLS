/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 04:49:41 by achazal           #+#    #+#             */
/*   Updated: 2014/11/25 22:54:45 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		free(ptr->path);
		past = ptr;
		ptr = ptr->next;
		free(past);
	}
}

void		ft_freefiles2(t_file **head, int flags)
{
	t_file	*ptr;
	t_file	*past;

	ptr = *head;
	while (ptr)
	{
		free(ptr->path);
		free(ptr->name);
		past = ptr;
		ptr = ptr->next;
		free(past);

	}
}