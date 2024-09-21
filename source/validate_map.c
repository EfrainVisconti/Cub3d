/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:47:40 by eviscont          #+#    #+#             */
/*   Updated: 2024/09/21 21:10:34 by usuario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	check_if_open(char **map, size_t last)
{
	size_t	i;
	size_t	j;
	size_t	cur_len;

	j = 0;
	while (map[j] != NULL)
	{
		i = 0;
		cur_len = ft_strlen(map[j]);
		while (map[j][i] != '\0')
		{
			if (j > 0 && cur_len > ft_strlen(map[j - 1]) \
			&& i > ft_strlen(map[j - 1]) - 1 \
			&& map[j][i] != '1' && map[j][i] != ' ')
				return (FALSE);
			if (j < last && cur_len > ft_strlen(map[j + 1]) \
			&& i > ft_strlen(map[j + 1]) - 1 \
			&& map[j][i] != '1' && map[j][i] != ' ')
				return (FALSE);
			i++;
		}
		j++;
	}
	return (TRUE);
}

int	check_map_spaces(t_map *map, int last)
{
	int	i;
	int	j;

	j = 0;
	while (j <= last)
	{
		i = 0;
		while (map->gamemap[j][i] != '\0')
		{
			if (map->gamemap[j][i] == '0')
			{
				if ((j > 0 && map->gamemap[j - 1][i] == ' ') || \
				(j < last && map->gamemap[j + 1][i] == ' ') || \
				(i > 0 && map->gamemap[j][i - 1] == ' ') || \
				(map->gamemap[j][i + 1] == ' '))
					return (FALSE);
			}
			i++;
		}
		j++;
	}
	return (TRUE);
}

int	check_map_walls_aux(t_map *map, int sec, int nlast)
{
	int	i;
	int	str_last;
	int	aux;

	while (sec <= nlast)
	{
		i = 0;
		str_last = ft_strlen(map->gamemap[sec]) - 1;
		aux = str_last + 1;
		if (map->map_size[1] < aux)
			map->map_size[1] = aux;
		while (map->gamemap[sec][i] == ' ')
			i++;
		if (map->gamemap[sec][i] != '1' && map->gamemap[sec][i] != '\0')
			return (FALSE);
		while (map->gamemap[sec][str_last] == ' ' && str_last != 0)
			str_last--;
		if (map->gamemap[sec][str_last] != '1' && map->gamemap[sec][i] != '\0')
			return (FALSE);
		sec++;
	}
	return (TRUE);
}

int	check_map_walls(t_map *map, int last)
{
	int	i;

	i = 0;
	while (map->gamemap[0][i] != '\0')
	{
		if (map->gamemap[0][i] != ' ' && map->gamemap[0][i] != '1')
			return (FALSE);
		i++;
	}
	i = 0;
	while (map->gamemap[last][i])
	{
		if (map->gamemap[last][i] != ' ' && map->gamemap[last][i] != '1')
			return (FALSE);
		i++;
	}
	if (!check_map_walls_aux(map, 1, last - 1))
		return (FALSE);
	return (TRUE);
}

int	validate_map(t_map *map)
{
	int	map_len;

	map_len = ft_str2dlen(map->gamemap);
	map->map_size[0] = map_len;
	if (!check_map_walls(map, map_len - 1))
		return (ft_printf("Error\nInvalid map walls\n"), FALSE);
	if (!check_if_open(map->gamemap, map_len - 1))
		return (ft_printf("Error\nMap is open\n"), FALSE);
	if (!check_map_spaces(map, map_len - 1))
		return (ft_printf("Error\nInvalid map spaces\n"), FALSE);
	return (TRUE);
}
