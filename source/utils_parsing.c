/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:23:50 by eviscont          #+#    #+#             */
/*   Updated: 2024/09/10 18:19:31 by usuario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	idx;

	idx = 0;
	while ((s1[idx] != '\0' && s2[idx] != '\0') && (s1[idx] == s2[idx]))
		idx++;
	return ((unsigned char)s1[idx] - (unsigned char)s2[idx]);
}

int	ft_arraylen(char **array)
{
	int	i;
	int	len;

	len = 0;
	i = -1;
	while (array[++i] != NULL)
		len++;
	return (len);
}
