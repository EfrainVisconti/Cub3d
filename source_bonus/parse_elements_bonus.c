/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:27:25 by eviscont          #+#    #+#             */
/*   Updated: 2024/09/19 20:03:41 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

int	coma_errors(char *str, int mode)
{
	int	aux;

	aux = 0;
	while (str[aux] != '\0')
	{
		if (str[aux] == ',' && (str[aux + 1] == ',' || aux == 0))
			return (TRUE);
		aux++;
	}
	if (mode == 1)
	{
		aux = ft_strlen(str);
		if (str[aux - 1] == ',')
			return (TRUE);
	}
	return (FALSE);
}

int	parse_fc_loop(t_map *map, char **splited, int i[4])
{
	char	**aux;

	while (splited[i[0]] != NULL)
	{
		if ((i[0] < i[3] - 1 && ft_strchr(splited[i[0]], ',') \
			&& !coma_errors(splited[i[0]], 0)) || \
			(i[0] == i[3] - 1 && !coma_errors(splited[i[0]], 1)))
		{
			aux = ft_split(splited[i[0]], ',');
			if (ft_str2dlen(aux) > 3)
				return (ft_free2dstr(aux), FALSE);
			i[1] = 0;
			while (aux[i[1]] != NULL && aux[i[1]][0] != '\0')
			{
				map->fc_aux[++i[2]] = cubed_atoi(aux[i[1]]);
				i[1]++;
			}
			ft_free2dstr(aux);
		}
		else
			return (FALSE);
		i[0]++;
	}
	return (TRUE);
}

int	parse_fc_aux(t_map *map, char **splited, int i[4])
{
	if (i[3] >= 2 && i[3] <= 4)
	{
		if (!parse_fc_loop(map, splited, i))
			return (ft_printf("Error\nInvalid %s format\n", splited[0]), FALSE);
		if (map->fc_aux[0] == -1 || map->fc_aux[1] == -1 || \
		map->fc_aux[2] == -1)
			return (ft_printf("Error\nInvalid %s format\n", splited[0]), FALSE);
	}
	else
		return (ft_printf("Error\nInvalid %s format\n", splited[0]), FALSE);
	return (flag_increase(map), TRUE);
}

int	parse_floor_ceiling(t_map *map, char **splited, int mode)
{
	int	i[4];

	i[0] = 1;
	i[1] = 0;
	i[2] = -1;
	i[3] = ft_str2dlen(splited);
	if (mode == F)
	{
		if (parse_fc_aux(map, splited, i) == TRUE)
		{
			map->f = rgb_to_hex(map->fc_aux[0], map->fc_aux[1], map->fc_aux[2]);
			ft_memset(map->fc_aux, -1, sizeof(map->fc_aux));
			return (TRUE);
		}
	}
	else
	{
		if (parse_fc_aux(map, splited, i) == TRUE)
		{
			map->c = rgb_to_hex(map->fc_aux[0], map->fc_aux[1], map->fc_aux[2]);
			ft_memset(map->fc_aux, -1, sizeof(map->fc_aux));
			return (TRUE);
		}
	}
	return (FALSE);
}

int	parse_textures(t_map *map, char **splited, int mode)
{
	if (ft_str2dlen(splited) != 2)
	{
		ft_printf("Error\nInvalid %s format\n", splited[0]);
		return (FALSE);
	}
	if (open(splited[1], O_RDONLY) == -1)
	{
		ft_printf("Error\nTexture %s not found\n", splited[0]);
		return (FALSE);
	}
	if (!valid_extension(splited[1], XPM))
	{
		ft_printf("Error\nTexture %s invalid extension\n", splited[0]);
		return (FALSE);
	}
	if (mode == NO)
		map->no = ft_strdup(splited[1]);
	else if (mode == SO)
		map->so = ft_strdup(splited[1]);
	else if (mode == WE)
		map->we = ft_strdup(splited[1]);
	else if (mode == EA)
		map->ea = ft_strdup(splited[1]);
	return (flag_increase(map), TRUE);
}
