/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 13:09:46 by dslogrov          #+#    #+#             */
/*   Updated: 2019/07/10 18:01:55 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

static char	isaflag(char byte)
{
	(void)byte;
	return (0);
}

static char	*flag_parse(char **argv[])
{
	char	flags[256];
	size_t	j;
	size_t	k;

	(*argv)++;
	k = 0;
	while (**argv && ***argv == '-')
	{
		if (!(**argv)[1] || (**argv)[1] == '-')
		{
			if ((**argv)[1] == '-')
				(*argv)++;
			break ;
		}
		j = 0;
		while (isaflag((**argv)[++j]))
			if (!ft_strchr(flags, (**argv)[j]))
				flags[k++] = (**argv)[j];
		if ((**argv)[j])
			exit(ft_printf_fd(2, "%s: invalid option -- '%c'\n",
				TOOL_NAME, (**argv)[j]));
		(*argv)++;
	}
	flags[k] = 0;
	if (k)
		return (ft_strdup(flags));
	return (NULL);
}

int			main(int argc, char *argv[])
{
	char		*flags;
	struct stat	stats;
	int			fd;

	(void)argc;
	flags = flag_parse(&argv);

	ft_printf("%s\n", flags);
	while (*argv)
	{
		fd = open(*argv, O_RDONLY);
		if (fstat(fd, &stats) == -1)
		{
			ft_printf_fd(2, "%s: '%s': ", TOOL_NAME,  *argv);
			perror(NULL);
		}
		else
			action(fd, stats, flags);
		close(fd);
		argv++;
	}
}
