/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:50:42 by eviscont          #+#    #+#             */
/*   Updated: 2024/09/10 17:21:40 by usuario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int valid_extension(char *str)
{
	int len;

	len = ft_strlen(str);
	if (len > 4)
	{
		if (str[len - 1] == 'b' && str[len - 2] == 'u' && str[len - 3] == 'c' && str[len - 4] == '.')
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

static void	check_line_aux(char *line, char **splited, int flag)
{
	if (!flag)
	{
		ft_printf("Error\n");
		ft_printf("Invalid or duplicated element found\n");
	}
	else
	{
		ft_printf("Error\n");
		ft_printf("Invalid map\n");
	}
	ft_free2dstr(splited);
	free(line);
}

int	case_no(t_map *map, char **splited)
{
	
}

int check_line(t_map *map, char *line, int flag)
{
	char **splited;

	splited = ft_split(line, ' ');
	if (!ft_strcmp("NO", splited[0]) && !map->no1)
		ft_printf("no\n");
	else if ((!ft_strcmp("SO", splited[0]) && !map->so1))
		ft_printf("so\n");
	else if ((!ft_strcmp("WE", splited[0]) && !map->we1))
		ft_printf("we\n");
	else if ((!ft_strcmp("EA", splited[0]) && !map->ea1))
		ft_printf("ea\n");
	else if ((!ft_strcmp("F", splited[0]) && !map->f1))
		ft_printf("f\n");
	else if ((!ft_strcmp("C", splited[0]) && !map->c1))
		ft_printf("c\n");
	else if (is_map_start(splited[0]) == TRUE)
	{
		map->start_map = TRUE;
		flag = 1;
	}
	else
		return (check_line_aux(line, splited, flag), FALSE);
	ft_free2dstr(splited);
	free(line);
	return (TRUE);
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
