/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 16:38:43 by dslogrov          #+#    #+#             */
/*   Updated: 2019/07/17 17:56:30 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

int	handle_archive(void *region, size_t size, char *name, char *flags)
{
	struct ar_hdr	header;
	const void		*end = region + size;
	size_t			name_len;

	region += SARMAG;
	header = *((struct ar_hdr *)(region));
	region += sizeof(header) + ft_atoi(header.ar_size);
	while (region < end)
	{
		header = *((struct ar_hdr *)(region));
		name_len = ft_strncmp(header.ar_name, "#1/", 3) ?
			0 : ft_atoi(header.ar_name + 3);
		ft_printf("%s(%s):\n", name, name_len ?
			region + sizeof(header) : header.ar_name);
		file_handle(region + sizeof(header) + name_len,
			ft_atoi(header.ar_size), NULL, flags);
		region += ft_atoi(header.ar_size) + sizeof(header);
	}
	return (errno);
}
//TODO: move this over to the other files, handle building
int	handle_mh(void *region, size_t size, char *name, char *flags)
{
	struct mach_header	header;
	const void			*end = region + size;

	region += sizeof(int32_t);
	header = *((struct mach_header *)(region));
	return (errno);
}

int handle_mh_64(void *region, size_t size, char *name, char *flags)
{
	struct mach_header_64		header;
	struct segment_command_64	segment;
	const void					*end = region + size;

	header = *((struct mach_header_64 *)(region));
	region += sizeof(header);
	while (header.ncmds--)
	{
		segment = *((struct segment_command_64 *)region);
		ft_printf("%s %x\n",segment.segname, segment.cmd);
		while (segment.nsects--)
		{

		}
		//Do stuff
		//TODO: fix offsets after __LINKEDIT
		region += segment.cmdsize;
	}
	return (errno);
}

int	file_handle(void *region, size_t size, char *name, char *flags)
{
	int32_t	magic;

	(void)flags;
	magic = *(int32_t *)region;
	if (!ft_strncmp(region, ARMAG, SARMAG))
		handle_archive(region, size, name, flags);
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
		handle_mh(region, size, name, flags);
	else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		handle_mh_64(region, size, name, flags);
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		(void)0;
	else if (magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64)
		(void)0;
	return (errno);
}
