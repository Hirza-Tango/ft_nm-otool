/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 06:21:45 by dslogrov          #+#    #+#             */
/*   Updated: 2019/07/24 14:48:13 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm_otool.h>

int	do_stuff_64(void *region, char swap, void *file)
{
	struct symtab_command		symtab;
	struct nlist_64				*list;

	if (((struct load_command *)region)->cmd != LC_SYMTAB)
		return (0);
	symtab = *((struct symtab_command *)region);

	list = (void *)file + endian_32(symtab.symoff, swap);
	while (symtab.nsyms--)
	{
		if (!list->n_un.n_strx)
			continue ;
		ft_printf("%s %u %p\n", file + symtab.stroff + list->n_un.n_strx, symtab.nsyms, list->n_value);
		list += sizeof(struct nlist_64);
	}
	return (0);
}

int	do_stuff_32(void *region, char swap, void *file)
{
	(void)(region && swap && file);
	return (0);
}
