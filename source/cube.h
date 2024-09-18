/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-orma <jde-orma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 02:02:54 by jde-orma          #+#    #+#             */
/*   Updated: 2024/09/05 02:02:54 by jde-orma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# include "../libraries/libft/source/libft.h"
# include "../libraries/minilibx-linux/mlx.h"

/* Game window settings */
# define SCREENW 1280
# define SCREENH 960
/* The .xpm i have are this size :*/
# define TEXTUREWIDTH 64
# define TEXTUREHEIGHT 64
/* For a FOV of 60 degrees -> tan(60/2) = 0.577*/
# define CAMERAANGLE 0.577
# define GAMENAME "CUB3D"
/* We are emulating a player/human, not a camera. Min wall distance to player*/
# define DISTANCETOWALL 0.5
# define MOV_SPEED 0.06
# define ROTATIONSPEED 0.04

/* Array positions for the textures*/
# define SO 0
# define NO 1
# define EA 2
# define WE 3

/* Axis value for the raycasting functions */
# define X_AXIS 0
# define Y_AXIS 1
# define X 0
# define Y 1

/* Linux qwerty key values */
# define UPARROW_KEY 65362
# define DOWNARROW_KEY 65364
# define RIGHTARROW_KEY 65363
# define LEFTARROW_KEY 65361
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define Q_KEY 113
# define ESC_KEY 65307

/* Movement management of the push/release of keys*/
# define ENABLE_MOVE 1
# define DISABLE_MOVE 0

/* Boolean (tipe int)*/
# define FALSE 0
# define TRUE 1

/* Movement functions modes defines */
# define RIGHT -1
# define LEFT 1
# define FORWARD 1
# define BACKWARD -1

/* Free functions modes */
# define FREE_TEXTURES 0
# define FREE_ALL 1

/* Valid_extension function modes */
# define CUB 0
# define XPM 1

/* Parse_floor_ceiling function modes */
# define F 0
# define C 1

/*
 map: The map as in the .cub file
 gamemap: The map copy the game uses. The player is erased.
*/
typedef struct s_map
{
	char		*map_line;
	int			nbr_player;
	char		**map;
	char		**gamemap;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			map_size[2];
	int			player_position[2];
	int			player_direction[2];
	int			f;
	int			c;
	int			start_map;
	int			fc_aux[3];
	int			p_flag;
}				t_map;

/*
 img: The main reference to the image that will be used in rendering.
 addr: A pointer to the image data, containing the pixel colors.
       This is used to access individual pixels during rendering.
 bits_per_pixel (bpp): Indicates how many bits are used to represent the color
                       of each pixel.
                       For example, 32 bits per pixel is common for
	                   images with RGBA color channels.
 size_line: The number of bytes needed to store a complete line of pixels in
              the image. This is important for calculating the memory position
			  of each pixel.
 endian: Determines whether the image uses big-endian or little-endian, which
         affects the byte order in the pixel color representation.
*/
typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		x;
	int		y;
}			t_img;

/* rayscreenposx: the ray's X axis position on the game screen*/
typedef struct s_ray
{
	double	rayscreenposx;
	double	raydir[2];
	int		map[2];
	double	sidedist[2];
	double	deltadist[2];
	int		step[2];
	double	perpwalldist;
	int		hit;
	int		wallfacehit;
}			t_ray;

/* dir and plane use the player initial position and direction as reference
   on an euclydian plane. Given that that means working on a Unitary circle
   ( radius == 1 ) the max and min values go from -1 to 1.
   Pos, in the other hand, references the player's current position on the
   map grid.
*/
typedef struct s_player
{
	double	pos[2];
	double	dir[2];
	double	plane[2];
	int		forward;
	int		bakcward;
	int		rotate_right;
	int		rotate_left;
}			t_player;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_w;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	t_player	player;
	int			screenwidth;
	int			screenheigth;
	int			**textures;
	t_map		map;
	t_img		img_buffer;
	t_img		texture[4];
}				t_data;

/*
 wallx: The horizontal position on the wall texture where the ray hits.
              Calculated using the player's position and the distance to the
			  wall. Adjusted to be in the range [0, 1) within the texture.
 texx: Horizontal coordinate in the texture for the current pixel on the screen
 	   Calculated by multiplying `wallx` by the texture width [TEXTUREWIDTH].
	   Adjusted based on the ray's direction to correct the orientation.
*/
typedef struct s_draw
{
	int		drawstart;
	int		drawend;
	int		texnum;
	int		texx;
	double	wallx;
	int		columnheight;
}			t_draw;

/* Utils */
int		ft_close(void *param);
void	ft_free_cub(char *str, t_map *cub, int mode);

/* Raycasting */
t_ray	ft_init_ray(t_data dt, int x);
void	ft_init_side(t_data dt, t_ray *ray);
int		ft_raycasting(void *param);
void	ft_raycasting_dda_algorithm(t_ray *ray, char **map);
int		ft_move(t_data *dt);
void	ft_get_draw_info(t_data dt, t_ray ray, t_draw *draw);
void	ft_mlx_put_line(t_data *data, int x, t_draw draw, int y);

/* Textures */
void	ft_free_textures(int **textures);
t_img	ft_read_texture(void *mlx, char *name, t_data *dt);

/* Game */
void	ft_game(t_map map);
int		ft_press_key(int key, void *param);
int		ft_release_key(int key, void *param);
void	ft_move_rotate(t_data *dt, double rotspeed, int sign);
void	ft_move_forward_backward(t_data *dt, double movespeed, int sign);

/* Init_parsing */
int		init_parsing(t_map *map, char *str, int fd, char *line);
char	*tabs_handler(char *str, int i, int j, int tabs);
int		check_line(t_map *map, char *line, int ret);
void	check_line_aux(char *line, char **splited);
int		is_map_start(t_map *map, char *str);
/* Parse_elements */
int		parse_textures(t_map *map, char **splited, int mode);
int		parse_floor_ceiling(t_map *map, char **splited, int mode);
int		parse_fc_aux(t_map *map, char **splited, int i[4]);
int		parse_fc_loop(t_map *map, char **splited, int i[4]);
int		rgb_to_hex(int r, int g, int b);
/* Parse_map */
int		parse_map(t_map *map, char *line);
int		check_items(char *line, t_map *map);
/* Check_map */
int		check_map(t_map *map);
int		check_empty_lines(char *line, int i, int found_doll);
void	erases_player_empty_lines(t_map *map);
void	get_player_pos_dir(t_map *map);
void	set_pos_dir(t_map *map, int mode, int i, int j);
/* Validate_map */
int		validate_map(t_map *map);
int		check_map_walls(t_map *map, int last);
int		check_map_walls_aux(t_map *map, int sec, int nlast);
int		check_map_spaces(t_map *map, int last);
/* Utils_parsing */
int		ft_strcmp(char *s1, char *s2);
int		cubed_atoi(const char *str);
int		valid_extension(char *str, int mode);
void	flag_increase(t_map *map);
char	*remove_eol(char *line);
/* Print_aux */
void	print_aux(t_map *map);
#endif
