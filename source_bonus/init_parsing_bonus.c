/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:50:42 by eviscont          #+#    #+#             */
/*   Updated: 2024/09/21 23:06:01 by usuario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

int	is_map_start(t_map *map, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '1' && str[i] != '0')
			return (FALSE);
		i++;
	}
	return (flag_increase(map), TRUE);
}

void	check_line_aux(char *line, int *ret)
{
	if (line && !only_spaces_line(line))
	{
		ft_printf("Error\n");
		ft_printf("Invalid map or invalid/duplicated element found\n");
		*ret = FALSE;
	}
	else
		*ret = TRUE;
}

int	check_line(t_map *map, char *line, int ret)
{
	char	**splited;

	splited = ft_split(remove_eol(line), ' ');
	if (!ft_strcmp("NO", splited[0]) && !map->no)
		ret = parse_textures(map, splited, NO);
	else if (!ft_strcmp("SO", splited[0]) && !map->so)
		ret = parse_textures(map, splited, SO);
	else if (!ft_strcmp("WE", splited[0]) && !map->we)
		ret = parse_textures(map, splited, WE);
	else if (!ft_strcmp("EA", splited[0]) && !map->ea)
		ret = parse_textures(map, splited, EA);
	else if (!ft_strcmp("F", splited[0]) && !map->f)
		ret = parse_floor_ceiling(map, splited, F);
	else if (!ft_strcmp("C", splited[0]) && !map->c)
		ret = parse_floor_ceiling(map, splited, C);
	else if (splited[0] && is_map_start(map, splited[0]) == TRUE)
	{
		ret = TRUE;
		map->start_map = TRUE;
	}
	else
		check_line_aux(line, &ret);
	ft_free2dstr(splited);
	free(line);
	return (ret);
}

char	*tabs_handler(char *str, int i, int j, int tabs)
{
	char	*aux;

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

int	init_parsing(t_map *map, char *str, int fd, char *line)
{
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
			if (map->start_map && map->p_flag == 7
				&& !parse_map(map, tabs_handler(line, -1, 0, 0)))
				return (free(line), FALSE);
			else if (map->start_map && map->p_flag != 7)
				return (print_error_aux(), free(line), 0);
		}
		free (line);
		line = ft_get_next_line(fd);
	}
	return (check_map(map));
}
