/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-orma <jde-orma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:52:55 by jde-orma          #+#    #+#             */
/*   Updated: 2024/09/05 00:52:55 by jde-orma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/* 

ft_init_side:
This function initializes the side distances for the raycasting algorithm.
Depending on the direction of the ray [raydir[X_AXIS], raydir[Y_AXIS]], 
it calculates the initial distance from the player position to the first 
grid line along the X and Y axes. 
[deltadist[X_AXIS], deltadist[Y_AXIS]] need to be positive for this calculus,
thus the fabs.
The [step[X_AXIS], step[Y_AXIS]] variables are set based on the ray
direction, determining whether the ray moves in a positive or negative
direction along the axes. 

The [sidedist[X_AXIS], sidedist[Y_AXIS]] variables represent the distance the
ray has to travel from its start position to the next X or Y side of the grid.

*/
void	ft_init_side(t_data data, t_ray *ray)
{
	if (ray->raydir[X_AXIS] < 0)
	{
		ray->step[X_AXIS] = -1;
		ray->sidedist[X_AXIS] = (data.player.pos[X_AXIS] - ray->map[X_AXIS]) * ray->deltadist[X_AXIS];
	}
	else
	{
		ray->step[X_AXIS] = 1;
		ray->sidedist[X_AXIS] = (ray->map[X_AXIS] + 1.0 - data.player.pos[X_AXIS])
			* ray->deltadist[X_AXIS];
	}
	if (ray->raydir[Y_AXIS] < 0)
	{
		ray->step[Y_AXIS] = -1;
		ray->sidedist[Y_AXIS] = (data.player.pos[Y_AXIS] - ray->map[Y_AXIS]) * ray->deltadist[Y_AXIS];
	}
	else
	{
		ray->step[Y_AXIS] = 1;
		ray->sidedist[Y_AXIS] = (ray->map[Y_AXIS] + 1.0 - data.player.pos[Y_AXIS])
			* ray->deltadist[Y_AXIS];
	}
}

/* 

 ft_init_ray:
 rayscreenposx = Calculates the ray position on the X axis of the window
 using the screenwidth as reference.
 [raydir[X_AXIS], raydir[Y_AXIS]] determine the ray position using the player
 position and FOV as reference.
 [deltadist[X_AXIS], deltadist[Y_AXIS]] determine de increment  for each
 cuadricule
 The `ft_init_side` function is called to further initialize the ray's side distances.
 
 */
t_ray	ft_init_ray(t_data data, int x)
{
	t_ray	ray;

	ray.hit = 0;
	ray.rayscreenposx = (2.0 * x / (double)data.screenwidth) - 1.0;
	ray.raydir[X_AXIS] = data.player.dir[X_AXIS] + (data.player.plane[X_AXIS] * ray.rayscreenposx);
	ray.raydir[Y_AXIS] = data.player.dir[Y_AXIS] + (data.player.plane[Y_AXIS] * ray.rayscreenposx);
	ray.map[X_AXIS] = (int)data.player.pos[X_AXIS];
	ray.map[Y_AXIS] = (int)data.player.pos[Y_AXIS];
	if (!ray.raydir[X_AXIS])
		ray.deltadist[X_AXIS] = 1e30;
	else
		ray.deltadist[X_AXIS] = fabs(1 / ray.raydir[X_AXIS]);
	if (!ray.raydir[Y_AXIS])
		ray.deltadist[Y_AXIS] = 1e30;
	else
		ray.deltadist[Y_AXIS] = fabs(1 / ray.raydir[Y_AXIS]);
	ft_init_side(data, &ray);
	return (ray);
}

/* 

 ft_raycasting_dda_algorithm:
 This function implements the Digital Differential Analyzer (DDA) algorithm,
 which steps the ray through the map one square at a time until it hits a wall.
 The DDA algorithm works by comparing the side distances [sidedist[X_AXIS],
 sidedist[Y_AXIS]] and advancing the ray to the next square in the map.
 Bare in mind that [deltadist[X_AXIS], deltadist[Y_AXIS]] are constant for each
 and every square the ray crossess
 When the ray hits a wall, the loop stops, and the `ray->hit` flag is set.
 The perpendicular wall distance (`ray->perpwalldist`) is calculated to ensure 
 accurate rendering and to correct for fish-eye distortion.

*/
void	ft_raycasting_dda_algorithm(t_ray *ray, char **map)
{
	while (ray->hit == 0)
	{
		if (ray->sidedist[X_AXIS] < ray->sidedist[Y_AXIS])
		{
			ray->sidedist[X_AXIS] += ray->deltadist[X_AXIS];
			ray->map[X_AXIS] += ray->step[X_AXIS];
			ray->wallfacehit = Y_AXIS;
		}
		else
		{
			ray->sidedist[Y_AXIS] += ray->deltadist[Y_AXIS];
			ray->map[Y_AXIS] += ray->step[Y_AXIS];
			ray->wallfacehit = X_AXIS;
		}
		if (map[ray->map[X_AXIS]][ray->map[Y_AXIS]] == '1')
			ray->hit = 1;
	}
	if (ray->wallfacehit == Y_AXIS)
		ray->perpwalldist = (ray->sidedist[X_AXIS] - ray->deltadist[X_AXIS]);
	else
		ray->perpwalldist = (ray->sidedist[Y_AXIS] - ray->deltadist[Y_AXIS]);
}

/* 

ft_get_draw_info:
This function calculates the necessary information to draw the vertical stripe
on the screen for to the current ray. It determines the height of the line to
be drawn [columnheight] based on the perpendicular wall distance [perpwalldist].
The starting [drawstart] and ending [drawend] points of the line are computed
to ensure it fits within the screen bounds.
The wall texture and texture X coordinate are selected based on which side 
of the wall was hit [side] and the exact location of the wall hit.

the ray hit the right side of a vertical wall, so the texture coordinates should be reversed
*/
void	ft_get_draw_info(t_data data, t_ray ray, t_draw *draw)
{
	draw->columnheight = (int)(data.screenheigth / ray.perpwalldist);
	draw->drawstart = data.screenheigth / 2 - draw->columnheight / 2;
	if (draw->drawstart < 0)
		draw->drawstart = 0;
	draw->drawend = draw->columnheight / 2 + data.screenheigth / 2;
	if (draw->drawend >= data.screenheigth)
		draw->drawend = data.screenheigth - 1;
	if (ray.wallfacehit == Y_AXIS && ray.raydir[X_AXIS] > 0)
		draw->texnum = NO;
	else if (ray.wallfacehit == Y_AXIS && ray.raydir[X_AXIS] < 0)
		draw->texnum = SO;
	else if (ray.wallfacehit == X_AXIS && ray.raydir[Y_AXIS] > 0)
		draw->texnum = EA;
	else if (ray.wallfacehit == X_AXIS && ray.raydir[Y_AXIS] < 0)
		draw->texnum = WE;
	if (ray.wallfacehit == Y_AXIS)
		draw->wallx = data.player.pos[Y_AXIS] + ray.perpwalldist * ray.raydir[Y_AXIS];
	else
		draw->wallx = data.player.pos[X_AXIS] + ray.perpwalldist * ray.raydir[X_AXIS];
	draw->wallx -= floor((draw->wallx));
	draw->texx = (int)(draw->wallx * (double)TEXTUREWIDTH);
	if (ray.wallfacehit == Y_AXIS && ray.raydir[X_AXIS] > 0)
		draw->texx = TEXTUREWIDTH - draw->texx - 1;
	if (ray.wallfacehit == X_AXIS && ray.raydir[Y_AXIS] < 0)
		draw->texx = TEXTUREWIDTH - draw->texx - 1;
}

/* 

ft_raycasting:
This is the main function that iterates over each pixel column on the screen
[screenwidth] to calculate and render the 3D view.
For each column, it initializes a ray [ray], executes the DDA algorithm 
to determine where the ray hits a wall, calculates the necessary drawing
information, and finally draws the corresponding line on the screen.
This process repeats for every column on the screen, thereby forming the 
complete scene image from the player's perspective.
This flow from ray initialization to scene rendering is the core of a 
raycasting engine, crucial for generating the first-person perspective.

*/
int	ft_raycasting(void *param)
{
	int		i;
	t_ray	ray;
	t_draw	draw;
	t_data	*data;

	i = 0;
	data = (t_data *)param;
	ft_move(data);
	data->img_buffer.img = mlx_new_image(data->mlx, SCREENWIDTH, SCREENHEIGTH);
	data->img_buffer.addr = (int *) mlx_get_data_addr(data->img_buffer.img,
			&data->img_buffer.bits_per_pixel, &data->img_buffer.size_line,
			&data->img_buffer.endian);
	while (i < data->screenwidth)
	{
		ray = ft_init_ray(*data, i);
		ft_raycasting_dda_algorithm(&ray, data->map.gamemap);
		ft_get_draw_info(*data, ray, &draw);
		ft_mlx_put_line(data, i, draw);
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_w, data->img_buffer.img, 0, 0);
	mlx_destroy_image(data->mlx, data->img_buffer.img);
	return (EXIT_SUCCESS);
}
