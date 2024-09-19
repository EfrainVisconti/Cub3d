/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:57:32 by eviscont          #+#    #+#             */
/*   Updated: 2024/09/19 17:20:45 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	print_aux(t_map *map)
{
	int	i;

	i = -1;
	ft_printf("GNL: %s\n", map->map_line);
	ft_printf("Map:\n");
	while (map->map[++i])
		ft_printf("%d:%s\n", i, map->map[i]);
	i = -1;
	ft_printf("Gamemap:\n");
	while (map->gamemap[++i])
		ft_printf("%d:%s\n", i, map->gamemap[i]);
	ft_printf("C: %x\nF: %x\n", map->c, map->f);
	ft_printf("NO: %s\n", map->no);
	ft_printf("SO: %s\n", map->so);
	ft_printf("WE: %s\n", map->we);
	ft_printf("EA: %s\n", map->ea);
	ft_printf("Mapsize: %d, %d\n", map->map_size[0], map->map_size[1]);
	ft_printf("Playerposition: ");
	ft_printf("%d, %d\n", map->player_position[0], map->player_position[1]);
	ft_printf("Playerdirection: ");
	ft_printf("%d, %d\n", map->player_direction[0], map->player_direction[1]);
}
