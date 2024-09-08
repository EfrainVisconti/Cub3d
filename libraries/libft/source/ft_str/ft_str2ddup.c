/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str2ddup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-orma <jde-orma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:10:39 by jde-orma          #+#    #+#             */
/*   Updated: 2024/06/22 15:10:39 by jde-orma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_str2ddup(char **str)
{
	int		len;
	char	**str2ddup;

	len = ft_str2dlen(str);
	str2ddup = (char **) malloc(sizeof(char *) * (len + 1));
	str2ddup[len--] = NULL;
	while (len >= 0)
	{
		str2ddup[len] = ft_strdup(str[len]);
		len--;
	}
	return (str2ddup);
}
