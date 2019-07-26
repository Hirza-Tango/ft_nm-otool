/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 06:42:38 by dslogrov          #+#    #+#             */
/*   Updated: 2019/07/26 17:48:10 by dslogrov         ###   ########.fr       */
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
    number = ((number << 8) & 0xFF00FF00FF00FF00ULL ) |
		((number >> 8) & 0x00FF00FF00FF00FFULL );
    number = ((number << 16) & 0xFFFF0000FFFF0000ULL ) |
		((number >> 16) & 0x0000FFFF0000FFFFULL );
    return (number << 32) | (number >> 32);
}
