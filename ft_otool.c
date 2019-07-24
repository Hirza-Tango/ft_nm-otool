/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 12:25:22 by dslogrov          #+#    #+#             */
/*   Updated: 2019/07/24 14:21:05 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm_otool.h>

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
