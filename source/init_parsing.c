/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:50:42 by eviscont          #+#    #+#             */
/*   Updated: 2024/09/15 21:32:13 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int valid_extension(char *str, int mode)
{
	int len;

	len = ft_strlen(str);
	if (mode == CUB && len > 4)
	{
		if (str[len - 1] == 'b' && str[len - 2] == 'u' && str[len - 3] == 'c' && str[len - 4] == '.')
			return (TRUE);
	}
	else if (mode == XPM && len > 4)
	{
		if (str[len - 1] == 'm' && str[len - 2] == 'p' && str[len - 3] == 'x' && str[len - 4] == '.')
			return (TRUE);
	}
	return (FALSE);
}

char *tabs_handler(char *str, int i, int j, int tabs)
{
	char *aux;

	while (str[++i] != '\0')
	{
		if (str[i] == '\t')
			tabs++;
	}
	aux = (char *)malloc(ft_strlen(str) + tabs * 3 + 1);
	if (!aux)
		return (NULL);
	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '\t')
		{
			aux[j++] = ' ';
			aux[j++] = ' ';
			aux[j++] = ' ';
			aux[j++] = ' ';
		}
		else
			aux[j++] = str[i];
	}
	aux[j] = '\0';
	return (aux);
}

static void	flag_increase(t_map *map)
{
	map->p_flag += 1;
}

static int	rgb_to_color_hex(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 0xFF);
}

int	is_map_start(t_map *map, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != '\n')
			return (FALSE);
		i++;
	}
	return (flag_increase(map), TRUE);
}

int	parse_floor_ceiling_aux(t_map *map, char **splited)
{
	int	len;
	int	i;
	int	j;
	int	k;
	char	*aux;
	char	**aux2;

	i = 1;
	k = -1;
	len = ft_str2dlen(splited);
	if (len >= 2 && len <= 4)
	{
		while (splited[i] != NULL)
		{
			aux = ft_strtrim(splited[i], "\n");
			if ((i < len - 1 && ft_strchr(aux, ',')) || (i == len -1 && !ft_strchr(aux, ',')) || (len == 2 && ft_strchr(aux, ',')))
			{
				aux2 = ft_split(aux, ',');
				if (ft_str2dlen(aux2) > 3)
					return (ft_printf("Error\nInvalid %s format\n", splited[0]), FALSE);
				j = 0;
				while (aux2[j] != NULL && aux2[j][0] != '\0')
				{
					map->fc_aux[++k] = cubed_atoi(aux2[j]);
					j++;
				}
			}
			else
				return (ft_printf("Error\nInvalid %s format\n", splited[0]), FALSE);
			i++;
		}
		if (map->fc_aux[0] == -1 || map->fc_aux[1] == -1 || map->fc_aux[2] == -1)
			return (ft_printf("Error\nInvalid %s format\n", splited[0]), FALSE);
	}
	else
		return (ft_printf("Error\nInvalid %s format\n", splited[0]), FALSE);
	return (flag_increase(map), TRUE);
}

int	parse_floor_ceiling(t_map *map, char **splited, int mode)
{
	if (mode == F)
	{
		if (parse_floor_ceiling_aux(map, splited) == TRUE)
		{
			map->f1 = rgb_to_color_hex(map->fc_aux[0], map->fc_aux[1], map->fc_aux[2]);
			ft_memset(map->fc_aux, -1, sizeof(map->fc_aux));
		}
		else
			return (FALSE);
	}
	else
	{
		if (parse_floor_ceiling_aux(map, splited) == TRUE)
		{
			map->c1 = rgb_to_color_hex(map->fc_aux[0], map->fc_aux[1], map->fc_aux[2]);
			ft_memset(map->fc_aux, -1, sizeof(map->fc_aux));
		}
		else
			return (FALSE);
	}
	return (TRUE);
}

int	parse_textures(t_map *map, char **splited, int mode, char *aux)
{
	if (ft_str2dlen(splited) != 2)
	{
		ft_printf("Error\nInvalid %s format\n", splited[0]);
		return (FALSE);
	}
	aux = ft_strtrim(splited[1], "\n");
	if (open(aux, O_RDONLY) == -1)
	{
		ft_printf("Error\nTexture %s not found\n", splited[0]);
		return (free(aux), FALSE);
	}
	if (!valid_extension(aux, XPM))
	{
		ft_printf("Error\nTexture %s invalid extension\n", splited[0]);
		return (free(aux), FALSE);
	}
	if (mode == NO)
		map->no1 = ft_strdup(aux);
	else if (mode == SO)
		map->so1 = ft_strdup(aux);
	else if (mode == WE)
		map->we1 = ft_strdup(aux);
	else if (mode == EA)
		map->ea1 = ft_strdup(aux);
	return (free(aux), flag_increase(map), TRUE);
}

static void	check_line_aux(char *line, char **splited)
{
	ft_printf("Error\n");
	ft_printf("Invalid map or invalid/duplicated element found\n");
	ft_free2dstr(splited);
	free(line);
}

int check_line(t_map *map, char *line, int ret)
{
	char **splited;

	splited = ft_split(line, ' ');
	if (!ft_strcmp("NO", splited[0]) && !map->no1)
		ret = parse_textures(map, splited, NO, NULL);
	else if ((!ft_strcmp("SO", splited[0]) && !map->so1))
		ret = parse_textures(map, splited, SO, NULL);
	else if ((!ft_strcmp("WE", splited[0]) && !map->we1))
		ret = parse_textures(map, splited, WE, NULL);
	else if ((!ft_strcmp("EA", splited[0]) && !map->ea1))
		ret = parse_textures(map, splited, EA, NULL);
	else if ((!ft_strcmp("F", splited[0]) && !map->f1))
		ret = parse_floor_ceiling(map, splited, F);
	else if ((!ft_strcmp("C", splited[0]) && !map->c1))
		ret = parse_floor_ceiling(map, splited, C);
	else if (is_map_start(map, splited[0]) == TRUE)
	{
		ret = TRUE;
		map->start_map = TRUE;
	}
	else
		return (check_line_aux(line, splited), FALSE);
	ft_free2dstr(splited);
	free(line);
	return (ret);
}

int	check_items(char *line, t_map *map)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'S'
		&& line[i] != 'E' && line[i] != 'W' && line[i] != ' ' && line[i] != '\n')
			return (ft_printf("Error\nInvalid items in map\n"), FALSE);
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			map->nbr_player++;
		i++;
	}
	return (TRUE);
}

int	parse_map(t_map *map, char *line)
{
	char	*temp;

	if (line != NULL && !check_items(line, map))
		return (FALSE);
	if (line != NULL)
	{
		temp = ft_strdup(map->map_line);
		free(map->map_line);
		map->map_line = ft_strjoin(temp, line);
		free(temp);
	}
	return (TRUE);
}

void	erases_player(t_map *map)
{
	int	i;

	i = 0;
	while (map->map_line[i] != '\0')
	{
		if (map->map_line[i] == 'N' || map->map_line[i] == 'S' || map->map_line[i] == 'E'
			|| map->map_line[i] == 'W')
			map->map_line[i] = '0';
		i++;
	}
}

int	check_map(t_map *map)
{
	if (map->nbr_player != 1)
		return (ft_printf("Error\nInvalid number of player\n"), FALSE);
	map->map1 = ft_split(map->map_line, '\n');
	if (!map->map1)
		return (ft_printf("Error\nGetting map\n"), FALSE);
	erases_player(map);
	map->gamemap1 = ft_split(map->map_line, '\n');
	if (!map->gamemap1)
		return (ft_printf("Error\nGetting gamemap\n"), FALSE);
	return (TRUE);
}

int check_cub_file(t_map *map, char *str)
{
	char	*line;
	int		fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error\nFile not found\n"), FALSE);
	line = ft_get_next_line(fd);
	if (line == NULL)
		return (ft_printf("Error\nEmpty map\n"), FALSE);
	while (line)
	{
		if (line != NULL)
		{
			if (ft_strcmp("\n", line) && !map->start_map)
			{
				if (!check_line(map, tabs_handler(line, -1, 0, 0), 0))
					return (free(line), FALSE);
			}
			if (map->start_map == TRUE && map->p_flag == 7 && !parse_map(map, tabs_handler(line, -1, 0, 0)))
				return (free(line), FALSE);
			else if (map->start_map == TRUE && map->p_flag != 7)
				return (ft_printf("Error\nMissing elements in file\n"), free(line), FALSE);
		}
		free (line);
		line = ft_get_next_line(fd);
	}
	return (check_map(map));
}
