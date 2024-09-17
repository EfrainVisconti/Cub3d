/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:23:50 by eviscont          #+#    #+#             */
/*   Updated: 2024/09/17 17:32:56 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	idx;

	idx = 0;
	if (!s1 || !s2)
		return (-1);
	while ((s1[idx] != '\0' && s2[idx] != '\0') && (s1[idx] == s2[idx]))
		idx++;
	return ((unsigned char)s1[idx] - (unsigned char)s2[idx]);
}

int	cubed_atoi(const char *str)
{
	int	numb;

	numb = 0;
	if (!str || !ft_isdigit(*str))
		return (-1);
	while (ft_isdigit(*str))
	{
		numb = 10 * numb + (*str - '0');
		if (numb < 0 || numb > 255)
			return (-1);
		str++;
	}
	if (*str)
		return (-1);
	return (numb);
}

int valid_extension(char *str, int mode)
{
	int len;

	len = ft_strlen(str);
	if (mode == CUB && len > 4)
	{
		if (str[len - 1] == 'b' && str[len - 2] == 'u' && str[len - 3] == 'c' && str[len - 4] == '.')
			return (TRUE);
	}
	else if (mode == XPM && len > 4)
	{
		if (str[len - 1] == 'm' && str[len - 2] == 'p' && str[len - 3] == 'x' && str[len - 4] == '.')
			return (TRUE);
	}
	return (FALSE);
}

int	rgb_to_color_hex(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 0xFF);
}

void	flag_increase(t_map *map)
{
	map->p_flag += 1;
}
