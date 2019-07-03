#include "ft_nm.h"

static char	isaflag(char byte)
{
	(void)byte;
	return 0;
}

static char	*flag_parse(char **argv[])
{
	char	flags[256];
	size_t	j;
	size_t	k;

	(*argv)++;
	k = 0;
	while (***argv == '-')
	{
		if (**argv[1] == '-')
		{
			(*argv)++;
			break ;
		}
		j = 0;
		while (isaflag(**argv[++j]))
			if (!ft_strchr(flags, **argv[j]))
				flags[k++] = **argv[j];
		if (*((*argv)++)[j])
			exit(ft_printf_fd(2, "nm: invalid option -- '%c'", *(*argv)++[j]));
	}
	flags[k] = 0;
	return ft_strdup(flags);
}

void	nm(int fd, struct stat stats, char *flags)
{
	void	*mount;

	(void)flags;
	mount = mmap(NULL, stats.st_size, PROT_READ, 0, fd, 0);
	// Do stuff

	munmap(mount, stats.st_size);
}

int		main(int argc, char *argv[])
{
	char		*flags;
	struct stat	stats;
	int			fd;

	(void)argc;
	flags = flag_parse(&(argv));
	while (argv)
	{
		fd = open(*argv, O_RDONLY);
		if (fstat(fd, &stats) == -1)
		{
			ft_printf_fd(2, "ft_nm: '%s'", argv);
			perror(NULL);
			ft_putendl("");
		}
		else
			nm(fd, stats, flags);
		close(fd);
	}
}
