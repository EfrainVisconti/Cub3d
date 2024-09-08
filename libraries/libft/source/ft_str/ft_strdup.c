/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-orma <jde-orma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:53:29 by jde-orma          #+#    #+#             */
/*   Updated: 2024/06/22 14:52:27 by jde-orma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s1)
{
	size_t		num;
	size_t		i;
	char		*sc1;

	i = 0;
	num = ft_strlen(s1) + 1;
	sc1 = (char *)ft_calloc(num, 1);
	if (!s1 || !sc1)
		return (NULL);
	while (s1[i])
	{
		sc1[i] = s1[i];
		i++;
	}
	sc1[i] = 0;
	return (sc1);
}
