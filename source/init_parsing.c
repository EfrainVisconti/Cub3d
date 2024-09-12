/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:50:42 by eviscont          #+#    #+#             */
/*   Updated: 2024/09/12 21:34:05 by eviscont         ###   ########.fr       */
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

int	is_map_start(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != '\n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static void	flag_increase(t_map *map)
{
	map->p_flag += 1;
}

int	parse_floor_ceiling(t_map *map, char **splited, int mode)
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
	if (len >= 2 && len <= 4 && mode == F)
	{
		while (splited[i] != NULL)
		{
			aux = ft_strtrim(splited[i], "\n");
			ft_printf("trimed: %s\n", aux);
			if ((i < len - 1 && ft_strchr(aux, ',')) || (i == len -1 && !ft_strchr(aux, ',')) || (len == 2 && ft_strchr(aux, ',')))
			{
				aux2 = ft_split(aux, ',');
				if (ft_str2dlen(aux2) > 3)
					return (ft_printf("Error\nInvalid %s format\n", splited[0]), FALSE);
				j = 0;
				while (aux2[j] != NULL && aux2[j][0] != '\0')
				{
					ft_printf("splited: %s\n", aux2[j]);
					ft_printf("1num: %i, %i\n", map->fc_aux[++k], j);
					map->fc_aux[k] = cubed_atoi(aux2[j]);
					ft_printf("2num: %i, %i, %i\n", map->fc_aux[k], k, j);
					j++;
				}
			}
			else
				return (ft_printf("Error\nInvalid %s format\n", splited[0]), FALSE);
			i++;
		}
		if (!map->fc_aux[0] || !map->fc_aux[1] || !map->fc_aux[2])
			return (ft_printf("Error\nInvalid %s format\n", splited[0]), FALSE);
	}
	else
		return (ft_printf("Error\nInvalid %s format\n", splited[0]), FALSE);
	return (flag_increase(map), TRUE);
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
		ret = parse_floor_ceiling(map, splited, F);
	else if (is_map_start(splited[0]) == TRUE)
	{
		map->p_flag += TRUE;
		ret = TRUE;
		map->start_map = TRUE;
	}
	else
		return (check_line_aux(line, splited), FALSE);
	ft_free2dstr(splited);
	free(line);
	return (ret);
}

int check_cub_file(t_map *map, char *str)
{
	char	*line;
	int		fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error\nFile not found\n"), FALSE);
	while (1)
	{
		line = ft_get_next_line(fd);
		if (line != NULL)
		{
			if (ft_strcmp("\n", line) && !map->start_map)
			{
				if (!check_line(map, tabs_handler(line, -1, 0, 0), 0))
					return (free(line), FALSE);
			}
			if (map->start_map == TRUE && map->p_flag == 7)
				ft_printf("we are in map ");
			else if (map->start_map == TRUE && map->p_flag != 7)
				return (ft_printf("Error\nMissing elements in file\n"), free(line), FALSE);
		}
		else
			break;
		free (line);
	}
	return (TRUE);
}
