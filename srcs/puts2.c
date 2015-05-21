/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 04:49:41 by achazal           #+#    #+#             */
/*   Updated: 2014/11/25 22:54:45 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int				ft_isnotlinktodir(char *path, int mode)
{
	struct stat	statbuf;
	char		*tmp;
	int			i;
	DIR			*dir;

	if (!S_ISLNK(mode))
		return (0);
	if ((dir = opendir(path)))
	{
		closedir(dir);
		return (0);
	}
	return (1);
}

void			ft_put_onwork_symbole(mode_t var, char *path)
{
	if (S_ISLNK(var))
		*path = 'l';
	else if ((var & 0170000) == 0040000)
		*path = 'd';
	else if ((var & 0170000) == 0020000)
		*path = 'c';
	else if ((var & 0170000) == 0060000)
		*path = 'b';
	else if ((var & 0170000) == 0010000)
		*path = 'p';
	else if ((var & 0170000) == 0140000)
		*path = 's';
	else
		*path = '-';
}

void			ft_put_onwork_value_loop(int n, char *path)
{
	if (n >= 10)
	{
		ft_put_onwork_value_loop(n / 10, path - 1);
		*path-- = n % 10 + '0';
	}
	else
		*path-- = n + '0';
}

void			ft_put_onwork_value(int n, char *path)
{
	if (n == -2147483648)
		ft_strcpyo(path, "-2147483648");
	else if (n == 0)
		ft_strcpyo(path, "0");
	else
	{
		if (n < 0)
		{
			*path-- = '-';
			n *= -1;
		}
		ft_put_onwork_value_loop(n, path);
	}
}

void			ft_put_devices(char *major, char *minor, int len, char *ptr)
{
	char		*p;

	p = minor;
	while (*p)
		p++;
	if (p != minor)
		p--;
	len -= (p - minor);
	while (p >= minor)
		*ptr-- = *p--;
	while (len--)
		ptr--;
	*ptr-- = ',';
	p = major;
	while (*p)
		p++;
	if (p != major)
		p--;
	while (p >= major)
		*ptr-- = *p--;
}
