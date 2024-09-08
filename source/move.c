/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-orma <jde-orma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:52:20 by jde-orma          #+#    #+#             */
/*   Updated: 2024/09/05 00:52:20 by jde-orma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/* 
ft_move_forward_backward:
This function handles player movement along the direction the player is facing.
It checks if the next position in the map grid [map.gamemap] is walkable
(i.e., not a wall) before updating the player's position [posx, posy].
The movement speed [movespeed] and direction [sign] are used to determine 
how far and in which direction to move the player (the work as steps)
The player's position is updated on their current direction vector [dirx, diry].
*/
void	ft_move_forward_backward(t_data *data, double movespeed, int sign)
{
	if (data->map.gamemap[(int)(data->player.pos[X_AXIS] + sign * 
			data->player.dir[X_AXIS] * movespeed)][(int)data->player.pos[Y_AXIS]] == '0')
		data->player.pos[X_AXIS] += sign * data->player.dir[X_AXIS] * movespeed;
	if (data->map.gamemap[(int)data->player.pos[X_AXIS]][(int)
			(data->player.pos[Y_AXIS] + sign * data->player.dir[Y_AXIS] * movespeed)] == '0')
		data->player.pos[Y_AXIS] += sign * data->player.dir[Y_AXIS] * movespeed;
}

/* 
ft_move_rotate:
This function handles the rotation of the player's view.
It rotates the direction vector [dirx, diry] & the camera plane[planex, planey]
by a given rotation speed [rotspeed]. 
The rotation is calculated using basic trigonometry, specifically the sine 
and cosine functions, to update the direction and plane vectors.
*/
void	ft_move_rotate(t_data *data, double rotspeed, int sign)
{
	double	tempdirx;
	double	tempplanex;

	tempdirx = data->player.dir[X_AXIS];
	tempplanex = data->player.plane[X_AXIS];
	data->player.dir[X_AXIS] = data->player.dir[X_AXIS] * cos(sign * rotspeed)
		- data->player.dir[Y_AXIS] * sin(sign * rotspeed);
	data->player.dir[Y_AXIS] = tempdirx * sin(sign * rotspeed)
		+ data->player.dir[Y_AXIS] * cos(sign * rotspeed);
	data->player.plane[X_AXIS] = data->player.plane[X_AXIS] * cos(sign * rotspeed)
		- data->player.plane[Y_AXIS] * sin(sign * rotspeed);
	data->player.plane[Y_AXIS] = tempplanex * sin(sign * rotspeed)
		+ data->player.plane[Y_AXIS] * cos(sign * rotspeed);
}

int	ft_press_key(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == D_KEY || key == RIGHTARROW_KEY)
		data->player.rotate_right = ENABLE_MOVE, printf("[posx, posy, dirx, diry, planex, plany][%f, %f, %f, %f, %f, %f]\n", data->player.pos[X_AXIS], data->player.pos[Y_AXIS], data->player.dir[X_AXIS], data->player.dir[Y_AXIS], data->player.plane[X_AXIS], data->player.plane[Y_AXIS]);
	else if (key == A_KEY || key == LEFTARROW_KEY)
		data->player.rotate_left = ENABLE_MOVE, printf("[posx, posy, dirx, diry, planex, plany][%f, %f, %f, %f, %f, %f]\n", data->player.pos[X_AXIS], data->player.pos[Y_AXIS], data->player.dir[X_AXIS], data->player.dir[Y_AXIS], data->player.plane[X_AXIS], data->player.plane[Y_AXIS]);
	else if (key == S_KEY || key == DOWNARROW_KEY)
		data->player.bakcward = ENABLE_MOVE, printf("[posx, posy, dirx, diry, planex, plany][%f, %f, %f, %f, %f, %f]\n", data->player.pos[X_AXIS], data->player.pos[Y_AXIS], data->player.dir[X_AXIS], data->player.dir[Y_AXIS], data->player.plane[X_AXIS], data->player.plane[Y_AXIS]);
	else if (key == W_KEY || key == UPARROW_KEY)
		data->player.forward = ENABLE_MOVE, printf("[posx, posy, dirx, diry, planex, plany][%f, %f, %f, %f, %f, %f]\n", data->player.pos[X_AXIS], data->player.pos[Y_AXIS], data->player.dir[X_AXIS], data->player.dir[Y_AXIS], data->player.plane[X_AXIS], data->player.plane[Y_AXIS]);
	else if (key == Q_KEY || key == ESC_KEY)
		ft_close(param);
	return (EXIT_SUCCESS);
}

int	ft_release_key(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == D_KEY || key == RIGHTARROW_KEY)
		data->player.rotate_right = DISABLE_MOVE;
	else if (key == A_KEY || key == LEFTARROW_KEY)
		data->player.rotate_left = DISABLE_MOVE;
	else if (key == S_KEY || key == DOWNARROW_KEY)
		data->player.bakcward = DISABLE_MOVE;
	else if (key == W_KEY || key == UPARROW_KEY)
		data->player.forward = DISABLE_MOVE;
	return (EXIT_SUCCESS);
}

int	ft_move(t_data *data)
{
	double	movespeed;
	double	rotspeed;

	movespeed = MOV_SPEED;
	rotspeed = ROTATIONSPEED;
	if (data->player.rotate_right)
		ft_move_rotate(data, rotspeed, RIGHT);
	if (data->player.rotate_left)
		ft_move_rotate(data, rotspeed, LEFT);
	if (data->player.forward)
		ft_move_forward_backward(data, movespeed, FORWARD);
	if (data->player.bakcward)
		ft_move_forward_backward(data, movespeed, BACKWARD);
	return (EXIT_SUCCESS);
}
