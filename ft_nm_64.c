/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 06:21:45 by dslogrov          #+#    #+#             */
/*   Updated: 2019/07/26 17:55:33 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm_otool.h>

char *g_name = "ft_nm";

//TODO: proper symbol lookup

char	type_parse(char n_type, char n_sect)
{
	char ret;

	if ((n_type & N_TYPE) == N_UNDF)
		ret = 'u';
	else if ((n_type & N_TYPE) == N_ABS)
		ret = 'a';
	else if ((n_type & N_TYPE) == N_INDR)
		ret = 'i';
	else if ((n_type & N_TYPE) == N_SECT)
	{
		if (n_sect == 1)
			ret = 't';
		else
			ret = 's';
	}
	else
		ret = '?';
	if (n_type & N_EXT)
		ret += 'A' - 'a';
	return (ret);
}

void	*sort_symbols(void *symbols, size_t n, size_t m, char *strtab)
{
	size_t	i;
	size_t	j;
	char	list[m];
	char	*tmp;

	tmp = malloc(n * m);
	ft_memcpy(tmp, symbols, n * m);
	i = 1;
	while (i < n)
	{
		j = i++;
		while (j > 0 && ((struct nlist *)(tmp + j * m))->n_un.n_strx && (
			!((struct nlist *)(tmp + (j - 1) * m))->n_un.n_strx ||
			strcmp(
				strtab + ((struct nlist *)(tmp + (j - 1) * m))->n_un.n_strx,
				strtab + ((struct nlist *)(tmp + j * m))->n_un.n_strx) > 0))
		{
			ft_memcpy(list, tmp + (j * m), m);
			ft_memcpy(tmp + (j * m), tmp + ((j - 1) * m), m);
			ft_memcpy(tmp + --j * m, list, m);
		}
	}
	return (tmp);
}

int		do_stuff_64(void *region, char swap, void *file)
{
	struct symtab_command	symtab;
	struct nlist_64			*list;
	struct nlist_64			*tmp;

	if (((struct load_command *)region)->cmd != LC_SYMTAB)
		return (0);
	symtab = *((struct symtab_command *)region);
	list = sort_symbols(file + endian_32(symtab.symoff, swap), symtab.nsyms,
		sizeof(struct nlist_64), file + symtab.stroff);
	tmp = list;
	while (symtab.nsyms--)
	{
		if (tmp->n_un.n_strx && !(tmp->n_type & N_STAB))
		{
			if (tmp->n_value)
				ft_printf("%016llx ", tmp->n_value);
			else
				ft_printf("%16s ", "");
			ft_printf("%c %s\n", type_parse(tmp->n_type, tmp->n_sect),
				file + symtab.stroff + tmp->n_un.n_strx);
		}
		tmp++;
	}
	free(list);
	return (0);
}

int		handle_mh_64(void *region, size_t size, char *name, char *flags)
{
	struct mach_header_64		header;
	const void					*file = region;

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
