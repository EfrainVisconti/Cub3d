/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:50:42 by eviscont          #+#    #+#             */
/*   Updated: 2024/09/12 01:44:46 by usuario          ###   ########.fr       */
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

int	parse_floor_ceiling(t_map *map, char **splited, int mode)
{
	int i;
	int	j;

	i = 1;
	while (splited[i] != NULL)
	{
		j = 0;
		while (splited[i][j] != '\0')
		{
			if (ft_atoi())
		}
	}
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
	return (free(aux), TRUE);
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
		ret = TRUE;
	else if ((!ft_strcmp("C", splited[0]) && !map->c1))
		ret = TRUE;
	else if (is_map_start(splited[0]) == TRUE)
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

int check_cub_file(t_map *map, char *str)
{
	char *line;
	int fd;

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
			if (map->start_map == TRUE)
				ft_printf("we are in map: %s\n", line);
		}
		else
			break;
		free (line);
	}
	return (TRUE);
}
