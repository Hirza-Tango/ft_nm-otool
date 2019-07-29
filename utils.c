/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 06:42:38 by dslogrov          #+#    #+#             */
/*   Updated: 2019/07/29 11:26:01 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

uint32_t	endian_32(uint32_t number, const char swap)
{
	if (!swap)
		return (number);
	number = ((number << 8) & 0xFF00FF00) | ((number >> 8) & 0xFF00FF);
	return (number << 16) | (number >> 16);
}

uint64_t	endian_64(uint64_t number, const char swap)
{
	if (!swap)
		return (number);
	number = ((number << 8) & 0xFF00FF00FF00FF00ULL) |
		((number >> 8) & 0x00FF00FF00FF00FFULL);
	number = ((number << 16) & 0xFFFF0000FFFF0000ULL) |
		((number >> 16) & 0x0000FFFF0000FFFFULL);
	return (number << 32) | (number >> 32);
}

char	type_parse(char n_type, char n_sect, char *sections)
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
		if (n_sect == sections[0])
			ret = 't';
		else if (n_sect == sections[1])
			ret = 'd';
		else if (n_sect == sections[2])
			ret = 'b';
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
