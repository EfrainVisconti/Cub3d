/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:57:32 by eviscont          #+#    #+#             */
/*   Updated: 2024/09/17 16:59:08 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	print_aux(t_map *map)
{
	int i = 0;
	while (map->map1[i])
	{
		ft_printf("%d:%s\n", i, map->map1[i]);
		i++;
	}
	i = 0;
	while (map->gamemap1[i])
	{
		ft_printf("%d:%s\n", i, map->gamemap1[i]);
		i++;
	}
}
