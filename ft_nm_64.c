/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 06:21:45 by dslogrov          #+#    #+#             */
/*   Updated: 2019/07/29 18:15:03 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm_otool.h>

char *g_name = "ft_nm";

int		do_stuff_64(void *region, char swap, void *file, char *sections)
{
	struct symtab_command	symtab;
	struct nlist_64			*list;
	struct nlist_64			*tmp;

	symtab = *((struct symtab_command *)region);
	list = sort_symbols(file + endian_32(symtab.symoff, swap), symtab.nsyms,
		sizeof(struct nlist_64), file + symtab.stroff);
	tmp = list;
	while (symtab.nsyms--)
	{
		if (tmp->n_un.n_strx && !(tmp->n_type & N_STAB))
		{
			if ((tmp->n_type & N_TYPE) != N_UNDF)
				ft_printf("%016llx ", tmp->n_value);
			else
				ft_printf("%16s ", "");
			ft_printf("%c %s\n", type_parse(tmp->n_type, tmp->n_sect, sections),
				file + symtab.stroff + tmp->n_un.n_strx);
		}
		tmp++;
	}
	free(list);
	return (0);
}

size_t	check_sections_64(char *sections, size_t segno, void *region)
{
	struct segment_command_64	segment;
	struct section_64			section;

	if (((struct load_command *)region)->cmd != LC_SEGMENT_64)
		return (0);
	segment = *((struct segment_command_64 *)region);
	region += sizeof(struct segment_command_64);
	while (segment.nsects--)
	{
		section = *((struct section_64 *)region);
		if (!strcmp(section.sectname, "__text")
			&& !strcmp(section.segname, "__TEXT"))
			sections[0] = segno;
		else if (!strcmp(section.sectname, "__data")
			&& !strcmp(section.segname, "__DATA"))
			sections[1] = segno;
		else if (!strcmp(section.sectname, "__bss")
			&& !strcmp(section.segname, "__DATA"))
			sections[2] = segno;
		segno++;
		region += sizeof(struct section_64);
	}
	return (segno);
}

int		handle_mh_64(void *region, size_t size, char *name, char *flags)
{
	const void				*file = region;
	struct mach_header_64	header;
	void					*symtab;
	size_t					segno;
	char					sections[3];

	(void)(size && flags);
	if (name)
		ft_printf("\n%s:\n", name);
	ft_bzero(sections, 3);
	segno = 1;
	header = *((struct mach_header_64 *)(region));
	region += sizeof(header);
	while (header.ncmds--)
	{
		if (((struct load_command *)region)->cmd == LC_SEGMENT_64)
			segno = check_sections_64(sections, segno, region);
		else if (((struct load_command *)region)->cmd == LC_SYMTAB)
			symtab = region;
		region += ((struct load_command *)region)->cmdsize;
	}
	return (do_stuff_64(symtab, header.magic == MH_CIGAM_64,
		(void *)file, sections));
}
