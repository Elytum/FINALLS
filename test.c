#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_RESET "\x1b[0m"

char					*ft_strjoin(char const *s1, char const *s2)
{
	register char		*str;
	register char		*ptr;

	if (s1 && !s2)
		return (strdup(s1));
	else if (!s1 && s2)
		return (strdup(s2));
	else if (!s1)
		return (NULL);
	if (!(str = (char *)malloc(sizeof(char) * \
		(strlen(s1) + strlen(s2) + 1))))
		return (NULL);
	ptr = str;
	while (*s1)
		*ptr++ = *s1++;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	return (str);
}

char					*ft_getfile(char *path)
{
	char				*str;
	char				*tmp;
	char				buff[127];
	FILE				*fp = fopen(path, "rb");

	str = NULL;
	while(!feof(fp))
	{
		bzero(buff, 127);
		if (fgets(buff, 126, fp))
		{
			tmp = ft_strjoin(str, buff);
			free(str);
			str = tmp;
		}
	}
	return (str);
}


void					ft_test_entry(char *path)
{
	char				*tmp;
	char				*str1;
	char				*str2;
	char				*file1;
	char				*file2;


	tmp = ft_strjoin("/bin/ls ", path);
	str1 = ft_strjoin(tmp, " > /tmp/file1");
	free(tmp);
	tmp = ft_strjoin("./ft_ls ", path);
	str2 = ft_strjoin(tmp, " > /tmp/file2");
	free(tmp);
	system(str1);
	system(str2);
	file1 = ft_getfile("/tmp/file1");
	file2 = ft_getfile("/tmp/file2");
	if (strcmp(file1, file2))
	{
		dprintf(1, "Command : %s vs %s\n", str1, str2);
		dprintf(1, "%sTest '%s' failed :\n", COLOR_RED, path);
		// dprintf(1, "'%s'\n\nVS\n\n'%s'\n\n", file1, file2);
		// dprintf(1, "%s\n\n", COLOR_RESET);
		exit (0);
	}
	else
		dprintf(1, "%sTest '%s' succeeded%s\n", COLOR_GREEN, path, COLOR_RESET);
	free(str1);
	free(str2);
	free(file1);
	free(file2);
}

int						main(void)
{
	char				*tmp;

	system("clear");
	ft_test_entry(".");
	ft_test_entry("-l");
	ft_test_entry("-l ..");
	ft_test_entry("-a ..");
	ft_test_entry("-r ..");
	ft_test_entry("-t ..");
	// ft_test_entry("-ll ..");
	// ft_test_entry("-la ..");
	// ft_test_entry("-lr ..");
	// ft_test_entry("-lt ..");
	// ft_test_entry("-al ..");
	ft_test_entry("-aa ..");
	ft_test_entry("-ar ..");
	ft_test_entry("-at ..");
	// ft_test_entry("-rl ..");
	ft_test_entry("-ra ..");
	ft_test_entry("-rr ..");
	ft_test_entry("-rt ..");
	// ft_test_entry("-tl ..");
	ft_test_entry("-ta ..");
	ft_test_entry("-tr ..");
	ft_test_entry("-tt ..");
	// ft_test_entry("-Rl /tmp/");
	ft_test_entry("-Ra /tmp/");
	ft_test_entry("-Rr /tmp/");
	ft_test_entry("-Rt /tmp/");
	// ft_test_entry("-lar ..");
	// ft_test_entry("-lat ..");
	// ft_test_entry("-alr ..");
	ft_test_entry("-art ..");
	// ft_test_entry("-ral ..");
	ft_test_entry("-rat ..");
	// ft_test_entry("-tal ..");
	ft_test_entry("-tar ..");
	ft_test_entry("-R /tmp");

	// ft_test_entry(".. -l");
	// ft_test_entry("-R");
	// ft_test_entry("-R /tmp");
}