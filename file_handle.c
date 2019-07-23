/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 16:38:43 by dslogrov          #+#    #+#             */
/*   Updated: 2019/07/23 18:50:08 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

int	handle_mh(void *region, size_t size, char *name, char *flags)
{
	struct mach_header	header;
	const void			*file = region;

	if (name)
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

int	handle_mh_64(void *region, size_t size, char *name, char *flags)
{
	struct mach_header_64		header;
	const void					*file = region;

	if (name)
		ft_printf("%s:\n", name);
	(void)(size && flags);
	header = *((struct mach_header_64 *)(region));
	region += sizeof(header);
	while (header.ncmds--)
	{
		do_stuff_64(region, header.magic == MH_CIGAM_64, (void *)file);
		region += ((struct load_command *)region)->cmdsize;
	}
	return (errno);
}

//TODO: find out what's messing with "gcc -c" file offsets
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

/*
** Since nm only supports mach-o binaries, only achictectures with supported
** mach-o binaries are read
*/

int	handle_fat(void *region, size_t size, char *name, char *flags)
{
	struct fat_header	header;
	struct fat_arch		arch;
	char				swap;

	header = *((struct fat_header *)(region));
	swap = header.magic == FAT_CIGAM;
	header.nfat_arch = endian_32(header.nfat_arch, swap);
	region += sizeof(struct fat_header);
	while (header.nfat_arch--)
	{
		arch = *((struct fat_arch *)(region));
		if (endian_32(arch.cputype, swap) == CPU_TYPE_I386)
			return (handle_mh(region + endian_32(arch.offset, swap),
				endian_32(arch.size, swap), name, flags));
		else if (endian_32(arch.cputype, swap) == CPU_TYPE_X86_64)
			return (handle_mh_64(region + endian_32(arch.offset, swap),
				endian_32(arch.size, swap), name, flags));
			region += sizeof(struct fat_arch);
	}
	(void)size;
	return (errno);
}

int	file_handle(void *region, size_t size, char *name, char *flags)
{
	uint32_t	magic;

	magic = *(int32_t *)region;
	if (!ft_strncmp(region, ARMAG, SARMAG))
		handle_archive(region, size, name, flags);
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
		handle_mh(region, size, name, flags);
	else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		handle_mh_64(region, size, name, flags);
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		handle_fat(region, size, name, flags);
	else if (magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64)
		(void)0;
	return (errno);
}
