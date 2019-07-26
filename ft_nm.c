/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 17:38:29 by dslogrov          #+#    #+#             */
/*   Updated: 2019/07/26 17:42:26 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm_otool.h>

//TODO: this

int		do_stuff_32(void *tmp, char swap, void *file)
{
	(void)(tmp && swap && file);
	return (0);
}

int	handle_mh(void *region, size_t size, char *name, char *flags)
{
	struct mach_header	header;
	const void			*file = region;

	if (name && !ft_strcmp(g_name, "ft_otool"))
		ft_printf("%s:\n", name);
	(void)(size && flags);
	header = *((struct mach_header *)(region));
	region += sizeof(header);
	while (header.ncmds--)
	{
		do_stuff_32(region, header.magic == MH_CIGAM, (void *)file);
		region += ((struct load_command *)region)->cmdsize;
	}
	return (errno);
}
