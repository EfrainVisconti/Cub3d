/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:27:25 by eviscont          #+#    #+#             */
/*   Updated: 2024/09/17 17:56:29 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
			map->f = rgb_to_color_hex(map->fc_aux[0], map->fc_aux[1], map->fc_aux[2]);
			ft_memset(map->fc_aux, -1, sizeof(map->fc_aux));
		}
		else
			return (FALSE);
	}
	else
	{
		if (parse_floor_ceiling_aux(map, splited) == TRUE)
		{
			map->c = rgb_to_color_hex(map->fc_aux[0], map->fc_aux[1], map->fc_aux[2]);
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
		map->no = ft_strdup(aux);
	else if (mode == SO)
		map->so = ft_strdup(aux);
	else if (mode == WE)
		map->we = ft_strdup(aux);
	else if (mode == EA)
		map->ea = ft_strdup(aux);
	return (free(aux), flag_increase(map), TRUE);
}
