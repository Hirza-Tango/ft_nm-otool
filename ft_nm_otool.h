/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_otool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 13:11:43 by dslogrov          #+#    #+#             */
/*   Updated: 2019/07/24 14:23:16 by dslogrov         ###   ########.fr       */
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

# include <stab.h>
# include <mach-o/fat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <ar.h>

# ifdef OTOOL
#  define TOOL_NAME "otool"
# elseif NM
#  define TOOL_NAME "nm"
# endif

extern char	*g_name;

int			file_handle(void *region, size_t size, char *name, char *flags);
int			isaflag(char flag);
int			do_stuff_64(void *command, char swap, void *file);
int			do_stuff_32(void *region, char swap, void *file);
uint64_t	endian_64(uint64_t number, const char swap);
uint32_t	endian_32(uint32_t number, const char swap);
#endif
