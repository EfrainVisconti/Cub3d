/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-orma <jde-orma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:51:41 by jde-orma          #+#    #+#             */
/*   Updated: 2024/09/05 00:51:41 by jde-orma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/* initializes the cub struct with a hardcoded map and textures */
void	ft_init_cub(t_map *map)
{
	ft_bzero(map, sizeof(t_map));
	map->start_map = 0;
	map->no = ft_strdup("assets/textures/NO.xpm");
	map->so = ft_strdup("assets/textures/SO.xpm");
	map->we = ft_strdup("assets/textures/WE.xpm");
	map->ea = ft_strdup("assets/textures/EA.xpm");
	map->gamemap = malloc(sizeof(char *) * 9);
	int i = 0;
	while (i < 8)
		map->gamemap[i++] = malloc(sizeof(char) * 20);
	strcpy(map->gamemap[0], "111111111111111111\0");
	strcpy(map->gamemap[1], "100000100000000001\0");
	strcpy(map->gamemap[2], "100000100000100011\0");
	strcpy(map->gamemap[3], "100000100000100011\0");
	strcpy(map->gamemap[4], "100000111111100011\0");
	strcpy(map->gamemap[5], "111011000000000001\0");
	strcpy(map->gamemap[6], "100000000000000011\0");
	strcpy(map->gamemap[7], "111111111111111111\0");
	map->gamemap[8] = NULL;
	map->c = 7829367;
	map->f = 3354412;
	map->map_size[0] = 8;
	map->map_size[1] = 20;
	/* The player position [X, Y] and direction [NO, SO, EA, WE] is extenalized here*/
	map->player_position[X_AXIS] = 8;
	map->player_position[Y_AXIS] = 3;
	map->player_direction[X_AXIS] = 0;
	map->player_direction[Y_AXIS] = -1;
	map->start_map = 109;
}

int	main(int argc, char **argv)
{
	t_map	map;

	(void)argc;
	(void)argv;
	ft_init_cub(&map);
	ft_game(map);
	ft_free_cub("Game ended\n", &map, FREE_ALL);
	return (EXIT_SUCCESS);
}
