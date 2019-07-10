/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 13:09:46 by dslogrov          #+#    #+#             */
/*   Updated: 2019/07/10 17:15:31 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void		nm(int fd, struct stat stats, char *flags)
{
	void	*mount;

	(void)flags;
	mount = mmap(NULL, stats.st_size, PROT_READ, 0, fd, 0);
	// Do stuff

	munmap(mount, stats.st_size);
}
