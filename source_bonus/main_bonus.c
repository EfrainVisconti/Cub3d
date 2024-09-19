/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-orma <jde-orma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:51:41 by jde-orma          #+#    #+#             */
/*   Updated: 2024/09/05 00:51:41 by jde-orma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

int	valid_extension(char *str, int mode)
{
	int	len;

	len = ft_strlen(str);
	if (mode == CUB && len > 4)
	{
		if (str[len - 1] == 'b' && str[len - 2] == 'u'
			&& str[len - 3] == 'c' && str[len - 4] == '.')
			return (TRUE);
	}
	else if (mode == XPM && len > 4)
	{
		if (str[len - 1] == 'm' && str[len - 2] == 'p'
			&& str[len - 3] == 'x' && str[len - 4] == '.')
			return (TRUE);
	}
	return (FALSE);
}

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
		return (ft_printf("Error:\nWrong number of arguments!"), 1);
	if (valid_extension(argv[1], CUB) == FALSE)
		return (ft_printf("Error:\nMap format is not .cub"), 1);
	ft_bzero(&map, sizeof(t_map));
	ft_memset(map.fc_aux, -1, sizeof(map.fc_aux));
	map.map_line = ft_strdup("");
	if (!init_parsing(&map, argv[1], 0, NULL))
	{
		ft_free_cub("", &map, FREE_ALL);
		return (EXIT_FAILURE);
	}
	ft_game(map);
	ft_free_cub("Game ended\n", &map, FREE_ALL);
	return (EXIT_SUCCESS);
}
