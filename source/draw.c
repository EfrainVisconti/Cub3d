/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-orma <jde-orma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/0 00:50:25 by jde-orma          #+#    #+#             */
/*   Updated: 2024/09/0 00:50:25 by jde-orma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*

 ft_mlx_put_pixel:
 This function plots a pixel on the screen at coordinates (x, y) with the given
 color.
 It calculates the memory address of the pixel within the image buffer
 [img_buffer.addr] based on the screen's resolution and the image format 
 (bits per pixel, line length, endian).
 The color value is then written directly to the calculated memory location.

*/
void	ft_mlx_put_pixel(t_data *data, int x, int y, int color)
{
	int	*dst;

	dst = data->img_buffer.addr + (y * data->img_buffer.size_line
			/ (data->img_buffer.bits_per_pixel / 8) + x);
	*(unsigned int *)dst = color;
}

/* 
 
 ft_mlx_put_line:
 This function draws a vertical line on the screen at column `x`, representing
 a wall slice in the 3D view. The line's starting and ending positions 
 [drawstart, drawend] and the corresponding texture are used to fill the 
 pixels with the correct texture color.
 The function steps through the texture vertically using the [textureyaxisstep]
 variable to map the wall segment to the screen accurately.
 The pixels above and below the line are filled with ceiling and floor colors.

*/
void	ft_mlx_put_line(t_data *data, int x, t_draw draw)
{
	int			y;
	int			texy;
	int			color;
	double		textureyaxisstep;
	double		texpos;

	y = 0;
	textureyaxisstep = 1.0 * TEXTUREHEIGHT / draw.columnheight;
	texpos = (draw.drawstart - data->screenheigth / 2 + draw.columnheight / 2)
		 * textureyaxisstep;
	while (y < SCREENHEIGTH)
	{
		if (y < draw.drawstart)
			color = data->map.c;
		else if (y >= draw.drawend)
			color = data->map.f;
		else
		{
			texy = (int)texpos & (TEXTUREHEIGHT - 1);
			texpos += textureyaxisstep;
			color = data->texture[draw.texnum].addr[TEXTUREHEIGHT * texy
				+ draw.texx];
		}
		ft_mlx_put_pixel(data, x, y, color);
		y++;
	}
}
