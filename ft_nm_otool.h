/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_otool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 13:11:43 by dslogrov          #+#    #+#             */
/*   Updated: 2019/07/29 11:27:06 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_OTOOL_H
# define FT_NM_OTOOL_H

# include "libft.h"
# include "ft_printf.h"

# include <errno.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/types.h>

# include <mach-o/fat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <ar.h>

extern char	*g_name;

int			file_handle(void *region, size_t size, char *name, char *flags);
int			handle_mh(void *region, size_t size, char *name, char *flags);
int			handle_mh_64(void *region, size_t size, char *name, char *flags);
uint32_t	endian_32(uint32_t number, const char swap);
uint64_t	endian_64(uint64_t number, const char swap);
void		*sort_symbols(void *symbols, size_t n, size_t m, char *strtab);
char		type_parse(char n_type, char n_sect, char *sections);
#endif
