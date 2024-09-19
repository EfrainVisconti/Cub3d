/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:34:54 by eviscont          #+#    #+#             */
/*   Updated: 2024/09/19 20:03:37 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	print_error_aux(void)
{
	ft_printf("Error\nMissing elements or map is not the last\n");
}

int	only_spaces_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	check_items(char *line, t_map *map)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != ' '
			&& line[i] != '\n' && line[i] != '$')
			return (ft_printf("Error\nInvalid items in map\n"), FALSE);
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
			map->nbr_player++;
		i++;
	}
	return (TRUE);
}

int	parse_map(t_map *map, char *line)
{
	char	*temp;

	if (line && line[0] == '\n')
	{
		free(line);
		line = ft_strdup("$\n");
	}
	if (line != NULL && !check_items(line, map))
		return (free(line), FALSE);
	if (line != NULL)
	{
		temp = ft_strdup(map->map_line);
		free(map->map_line);
		map->map_line = ft_strjoin(temp, line);
		free(temp);
	}
	free(line);
	return (TRUE);
}
