/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-orma <jde-orma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 09:42:28 by jde-orma          #+#    #+#             */
/*   Updated: 2024/06/22 14:52:27 by jde-orma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dst_cpy;
	const char	*src_cpy;

	dst_cpy = (char *)dst;
	src_cpy = (const char *)src;
	if (!len)
		return (dst);
	if (dst <= src)
		return (ft_memcpy(dst, src, len));
	while (len--)
		dst_cpy[len] = src_cpy[len];
	return (dst);
}
