/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_otool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 13:11:43 by dslogrov          #+#    #+#             */
/*   Updated: 2019/07/10 18:01:40 by dslogrov         ###   ########.fr       */
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

int				action(int fd, struct stat stats, char *flags);
#endif
