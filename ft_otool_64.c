/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_64.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 12:25:22 by dslogrov          #+#    #+#             */
/*   Updated: 2019/07/29 14:19:54 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm_otool.h>

char *g_name = "ft_otool";

int	do_stuff_64(void *region, char swap, void *file)
{
	struct segment_command_64	segment;
	struct section_64			section;

	(void)swap;
	if (((struct load_command *)region)->cmd != LC_SEGMENT_64)
		return (0);
	segment = *((struct segment_command_64 *)region);
	region += sizeof(struct segment_command_64);
	while (segment.nsects--)
	{
		section = *((struct section_64 *)region);
		if (!strcmp(section.sectname, "__text")
			&& !strcmp(section.segname, "__TEXT"))
		{
			ft_printf("Contents of (__TEXT,__text) section\n");
			ft_hexdump(file + section.offset, section.size,
			(off_t)section.addr, 1);
			return (1);
		}
		region += sizeof(struct section_64);
	}
	return (0);
}

int	handle_mh_64(void *region, size_t size, char *name, char *flags)
{
	struct mach_header_64		header;
	const void					*file = region;

	(void)(size && flags);
	header = *((struct mach_header_64 *)(region));
	region += sizeof(header);
	if (name)
		ft_printf("%s:\n", name);
	while (header.ncmds--)
	{
		do_stuff_64(region, header.magic == MH_CIGAM_64, (void *)file);
		region += ((struct load_command *)region)->cmdsize;
	}
	return (errno);
}
