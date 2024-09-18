/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:41:38 by eviscont          #+#    #+#             */
/*   Updated: 2024/09/18 23:05:25 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	set_pos_dir(t_map *map, int mode, int i, int j)
{
	map->player_position[X_AXIS] = i;
	map->player_position[Y_AXIS] = j;
	if (mode == NO)
	{
		map->player_direction[X_AXIS] = 0;
		map->player_direction[Y_AXIS] = -1;
	}
	else if (mode == SO)
	{
		map->player_direction[X_AXIS] = 0;
		map->player_direction[Y_AXIS] = 1;
	}
	else if (mode == EA)
	{
		map->player_direction[X_AXIS] = 1;
		map->player_direction[Y_AXIS] = 0;
	}
	else if (mode == WE)
	{
		map->player_direction[X_AXIS] = -1;
		map->player_direction[Y_AXIS] = 0;
	}
}

void	get_player_pos_dir(t_map *map)
{
	int	i;
	int	j;

	j = 0;
	while (map->map[j] != NULL)
	{
		i = 0;
		while (map->map[j][i] != '\0')
		{
			if (map->map[j][i] == 'N')
				set_pos_dir(map, NO, i, j);
			else if (map->map[j][i] == 'S')
				set_pos_dir(map, SO, i, j);
			else if (map->map[j][i] == 'E')
				set_pos_dir(map, EA, i, j);
			else if (map->map[j][i] == 'W')
				set_pos_dir(map, WE, i, j);
			i++;
		}
		j++;
	}
}

void	erases_player_empty_lines(t_map *map)
{
	int	i;

	i = 0;
	while (map->map_line[i] != '\0')
	{
		if (map->map_line[i] == 'N' || map->map_line[i] == 'S'
			|| map->map_line[i] == 'E' || map->map_line[i] == 'W')
			map->map_line[i] = '0';
		if (map->map_line[i] == '$')
			map->map_line[i] = '\n';
		i++;
	}
}

int	check_empty_lines(char *line, int i, int found_doll)
{
	while (line[i] != '\0')
	{
		if (line[i] == '$')
		{
			if (found_doll == FALSE)
				found_doll = TRUE;
			if (line[i + 1] == '\n' || line[i + 1] == '\0')
			{
				i++;
				if (line[i] == '\n')
					i++;
				continue ;
			}
			else
				return (FALSE);
		}
		else
		{
			if (found_doll)
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	check_map(t_map *map)
{
	if (!map->start_map)
		return (ft_printf("Error\nMissing map\n"), FALSE);
	if (map->nbr_player != 1)
		return (ft_printf("Error\nInvalid number of player\n"), FALSE);
	if (!check_empty_lines(map->map_line, 0, FALSE))
		return (ft_printf("Error\nInvalid map\n"), FALSE);
	map->map = ft_split(map->map_line, '\n');
	if (!map->map)
		return (ft_printf("Error\nGetting map\n"), FALSE);
	erases_player_empty_lines(map);
	map->gamemap = ft_split(map->map_line, '\n');
	if (!map->gamemap || !map->gamemap[0])
		return (ft_printf("Error\nGetting gamemap\n"), FALSE);
	if (!validate_map(map))
		return (FALSE);
	get_player_pos_dir(map);
	print_aux(map);
	return (TRUE);
}
