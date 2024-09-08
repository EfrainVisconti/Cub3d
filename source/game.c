/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-orma <jde-orma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:51:05 by jde-orma          #+#    #+#             */
/*   Updated: 2024/09/05 00:51:05 by jde-orma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_free_cub(char *str, t_map *map, int mode)
{
	printf("%s", str);
	free(map->no);
	free(map->so);
	free(map->we);
	free(map->ea);
	if (mode == FREE_ALL)
	{
		// ft_free2dstr(map->map);
		ft_free2dstr(map->gamemap);
	}
	exit(EXIT_SUCCESS);
}

/* Function responsible of seamlessly exiting cub3D when the user closes
   the window*/
int	ft_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	mlx_destroy_window(data->mlx, data->mlx_w);
	ft_free_cub("Game exited\n", &data->map, FREE_ALL);
	exit(EXIT_SUCCESS);
}

/* Initialises the data structure*/
void	ft_init_data(t_data *data, t_map map)
{
	data->map = map;
	data->mlx = mlx_init();
	data->screenwidth = SCREENWIDTH;
	data->screenheigth = SCREENHEIGTH;
	data->player.forward = DISABLE_MOVE;
	data->player.bakcward = DISABLE_MOVE;
	data->player.rotate_right = DISABLE_MOVE;
	data->player.rotate_left = DISABLE_MOVE;
	data->texture[SO] = ft_read_texture(data->mlx, data->map.so, data);
	data->texture[NO] = ft_read_texture(data->mlx, data->map.no, data);
	data->texture[EA] = ft_read_texture(data->mlx, data->map.ea, data);
	data->texture[WE] = ft_read_texture(data->mlx, data->map.we, data);
	data->player.pos[X_AXIS] = (double)map.player_position[Y_AXIS] + DISTANCETOWALL;
	data->player.pos[Y_AXIS] = (double)map.player_position[X_AXIS] + DISTANCETOWALL;
	data->player.dir[X_AXIS] = (double)map.player_direction[Y_AXIS];
	data->player.dir[Y_AXIS] = (double)map.player_direction[X_AXIS];
	data->player.plane[X_AXIS] = data->player.dir[Y_AXIS] * (CAMERAANGLE);
	data->player.plane[Y_AXIS] = data->player.dir[X_AXIS] * (-CAMERAANGLE);
	data->mlx_w = mlx_new_window(data->mlx, SCREENWIDTH, SCREENHEIGTH, GAMENAME);
}

/* Main "loop" of the cub3d. The raycasting function is called here */
void	ft_game(t_map map)
{
	t_data	data;

	ft_init_data(&data, map);
	mlx_hook(data.mlx_w, 2, (1L << 0), *ft_press_key, &data);
	mlx_hook(data.mlx_w, 3, (1L << 1), *ft_release_key, &data);
	mlx_loop_hook(data.mlx, &ft_raycasting, &data);
	mlx_hook(data.mlx_w, 17, 0, &ft_close, &data);
	mlx_loop(data.mlx);
}
