/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 17:41:40 by dslogrov          #+#    #+#             */
/*   Updated: 2019/07/26 17:56:26 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm_otool.h>

int	do_stuff_32(void *region, char swap, void *file)
{
	struct segment_command	segment;
	struct section			section;

	(void)swap;
	if (((struct load_command *)region)->cmd != LC_SEGMENT)
		return (0);
	segment = *((struct segment_command *)region);
	region += sizeof(struct segment_command);
	while (segment.nsects--)
	{
		section = *((struct section *)region);
		if (!strcmp(section.sectname, "__text")
			&& !strcmp(section.segname, "__TEXT"))
		{
			ft_printf("Contents of (__TEXT,__text) section\n");
			ft_hexdump(file + section.offset, section.size,
			(off_t)section.addr, 1);
			return (1);
		}
		region += sizeof(struct section);
	}
	return (0);
}

int	handle_mh(void *region, size_t size, char *name, char *flags)
{
	struct mach_header	header;
	const void			*file = region;

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
