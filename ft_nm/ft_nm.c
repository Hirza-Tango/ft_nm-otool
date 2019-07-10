/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 13:09:46 by dslogrov          #+#    #+#             */
/*   Updated: 2019/07/10 17:59:10 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		handle_archive(void)
{

}

int		action(int fd, struct stat stats, char *flags)
{
	void	*mount;
	int32_t	magic;

	(void)flags;
	mount = mmap(NULL, stats.st_size, PROT_READ, 0, fd, 0);
	magic = *(int32_t *)mount;
	if (ft_strncmp(mount, ARMAG, SARMAG))
		handle_archive();
	else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		(void)0;
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
		(void)0;
	munmap(mount, stats.st_size);
}
