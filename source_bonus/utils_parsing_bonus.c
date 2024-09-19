/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:23:50 by eviscont          #+#    #+#             */
/*   Updated: 2024/09/19 20:02:51 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

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

void	flag_increase(t_map *map)
{
	map->p_flag += 1;
}

char	*remove_eol(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
			line[i] = ' ';
		i++;
	}
	return (line);
}

int	rgb_to_hex(int r, int g, int b)
{
	return (0xFF000000 | r << 16 | g << 8 | b);
}
