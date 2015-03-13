// #include "../includes/ft_ls.h"
// #include <grp.h>
// #include <pwd.h>
// #include <sys/stat.h>
// #include <sys/types.h>


#include "../includes/ft_ls.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>

char				ft_getsymbole(struct stat filestat)
{
	if ((filestat.st_mode & 0170000) == 0040000)
		return ('d');
	if ((filestat.st_mode & 0170000) == 0120000)
		return ('l');
	if ((filestat.st_mode & 0170000) == 0020000)
		return ('c');
	if ((filestat.st_mode & 0170000) == 0060000)
		return ('b');
	if ((filestat.st_mode & 0170000) == 0010000)
		return ('p');
	if ((filestat.st_mode & 0170000) == 0140000)
		return ('s');
	return ('-');
}

char				*ft_get_permissions(struct stat filestat)
{
	char			*permissions;

	permissions = (char *)malloc(sizeof(char) * (10 + 1));
	permissions[0] = ft_getsymbole(filestat);
	permissions[1] = ((filestat.st_mode & S_IRUSR) ? 'r' : '-');
	permissions[2] = ((filestat.st_mode & S_IWUSR) ? 'w' : '-');
	permissions[3] = ((filestat.st_mode & S_IXUSR) ? 'x' : '-');
	permissions[4] = ((filestat.st_mode & S_IRGRP) ? 'r' : '-');
	permissions[5] = ((filestat.st_mode & S_IWGRP) ? 'w' : '-');
	permissions[6] = ((filestat.st_mode & S_IXGRP) ? 'x' : '-');
	permissions[7] = ((filestat.st_mode & S_IROTH) ? 'r' : '-');
	permissions[8] = ((filestat.st_mode & S_IWOTH) ? 'w' : '-');
	permissions[9] = ((filestat.st_mode & S_IXOTH) ? 'x' : '-');
	permissions[10] = '\0';
	return (permissions);
}

char				*ft_get_owner(struct stat filestat)
{
	struct passwd	*pw;
	char			*str;

	pw = getpwuid(filestat.st_uid);
	if (!pw)
		str = NULL;
	else
		str = ft_strdup(pw->pw_name);
	return (str);
}

char				*ft_get_group(struct stat filestat)
{
	struct group	*gr;
	char			*str;

	gr = getgrgid(filestat.st_gid);
	if (!gr)
		str = NULL;
	else
		str = ft_strdup(gr->gr_name);
	return (str);
}