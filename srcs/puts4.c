#include <ft_ls.h>
#define S_ISISVTX 0001000
#define S_ISUID   0004000
#define S_ISGID   0002000
#define XATTR_SIZE 10000
#include <sys/xattr.h>

static void			ft_first(mode_t var, char **path)
{
	if (var & S_ISISVTX)
	{
		
		if (var & S_IWOTH || var & S_IROTH)
		{
			*(*path)-- = 't';
			*(*path)-- = ((var & S_IWOTH) ? 'w' : '-');
			*(*path)-- = ((var & S_IROTH) ? 'r' : '-');
		}
		else
		{
			*(*path)-- = 'T';
			*(*path)-- = '-';
			*(*path)-- = '-';
		}
	}
	else
	{
		*(*path)-- = ((var & S_IXOTH) ? 'x' : '-');
		*(*path)-- = ((var & S_IWOTH) ? 'w' : '-');
		*(*path)-- = ((var & S_IROTH) ? 'r' : '-');
	}
}

static void			ft_second(mode_t var, char **path)
{
	if (var & S_ISGID)
	{
		if (var & S_IXGRP || var & S_IXGRP)
		{
			*(*path)-- = 's';
			*(*path)-- = ((var & S_IWGRP) ? 'w' : '-');
			*(*path)-- = ((var & S_IRGRP) ? 'r' : '-');
		}
		else
		{
			*(*path)-- = 'S';
			*(*path)-- = '-';
			*(*path)-- = '-';
		}
	}
	else
	{
		*(*path)-- = ((var & S_IXGRP) ? 'x' : '-');
		*(*path)-- = ((var & S_IWGRP) ? 'w' : '-');
		*(*path)-- = ((var & S_IRGRP) ? 'r' : '-');
	}
}

static void			ft_third(mode_t var, char **path)
{
	if (var & S_ISUID)
	{
		if (var & S_IXUSR || var & S_IWUSR)
		{
			*(*path)-- = 's';
			*(*path)-- = ((var & S_IWUSR) ? 'w' : '-');
			*(*path)-- = ((var & S_IRUSR) ? 'r' : '-');
		}
		else
		{
			*(*path)-- = 'S';
			*(*path)-- = '-';
			*(*path)-- = '-';
		}
	}
	else
	{
		*(*path)-- = ((var & S_IXUSR) ? 'x' : '-');
		*(*path)-- = ((var & S_IWUSR) ? 'w' : '-');
		*(*path)-- = ((var & S_IRUSR) ? 'r' : '-');
	}
}

void				ft_put_onwork_permissions(mode_t var, char *path, char *p)
{
	if (listxattr(p, NULL, 0, XATTR_NOFOLLOW) > 0)
		*path-- = '@';
	else
		path--;
	ft_first(var, &path);
	ft_second(var, &path);
	ft_third(var, &path);	
	ft_put_onwork_symbole(var, path);
}