/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:50:42 by eviscont          #+#    #+#             */
/*   Updated: 2024/09/09 21:10:50 by eviscont         ###   ########.fr       */
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
	return (free(str), aux);
}

int	is_horizontal_wall(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '1')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int check_line(t_map *map, char *line)
{
	char **splited;

	splited = ft_split(line, ' ');
	if (ft_strcmp("NO", splited[0]) && !map->no)
		putchar('c');
	else if ((ft_strcmp("SO", splited[0]) && !map->so))
		putchar('c');
	else if ((ft_strcmp("WE", splited[0]) && !map->we))
		putchar('c');
	else if ((ft_strcmp("EA", splited[0]) && !map->ea))
		putchar('c');
	else if ((ft_strcmp("EA", splited[0]) && !map->ea))
		putchar('c');
	else if ((ft_strcmp("F", splited[0]) && !map->f))
		putchar('c');
	else if ((ft_strcmp("C", splited[0]) && !map->c))
		putchar('c');
	else if (is_horizontal_wall(splited[0]))

}

int check_cub_file(t_map *map, char *str)
{
	char *line;
	int fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error\nFile not found"), FALSE);
	while (1)
	{
		line = get_next_line(fd);
		if (line != NULL)
		{
			if (ft_strcmp("", line) && !map->start_map)
				check_line(map, tabs_handler(line, -1, 0, 0));
			free(line);
		}
		else
			break;
	}
	return (TRUE);
}
