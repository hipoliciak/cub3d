/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:06:57 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/13 01:04:53 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_elements(t_game *game, char **mapf_tab)
{
	int	i;
	int	j;

	i = 0;
	game->player.dir = '0';
	while (mapf_tab[i])
	{
		j = 0;
		while (mapf_tab[i][j])
		{
			while (ft_isspace_not_nl(mapf_tab[i][j]))
				j++;
			if (!(ft_strchr("10NEWS", mapf_tab[i][j])))
				return (1);
			if (ft_strchr("NEWS", mapf_tab[i][j]) && game->player.dir != '0')
				return (1);
			if (ft_strchr("NEWS", mapf_tab[i][j]) && game->player.dir == '0')
				game->player.dir = mapf_tab[i][j];
			j++;
		}
		i++;
	}
	return (0);
}

int	check_map_top_bottom(char **mapf_tab, int i, int j)
{
	if (!mapf_tab || !mapf_tab[i] || !mapf_tab[i][j])
		return (1);
	while (ft_isspace_not_nl(mapf_tab[i][j]))
		j++;
	while (mapf_tab[i][j])
	{
		if (mapf_tab[i][j] != '1')
			return (1);
		j++;
	}
	return (0);
}

int	check_map_borders(t_map *map, char **mapf_tab)
{
	int	i;
	int	j;

	if (check_map_top_bottom(mapf_tab, 0, 0))
		return (1);
	i = 1;
	while (i < (map->height - 1))
	{
		j = ft_strlen(mapf_tab[i]) - 1;
		if (mapf_tab[i][j] != '1')
			return (1);
		i++;
	}
	if (check_map_top_bottom(mapf_tab, i, 0))
		return (1);
	return (0);
}

int	check_map(t_game *game, char **mapf_tab)
{
	if (!game->mapf)
		return (err("Map not found", 1));
	if (check_map_borders(&game->map, mapf_tab))
		return (err("Invalid map borders", 1));
	if (game->map.height < 3)
		return (err("Map too small", 1));
	if (check_map_elements(game, mapf_tab))
		return (err("Invalid map elements", 1));
	if (check_player_position(game, mapf_tab))
		return (err("Invalid player position", 1));
	return (0);
}
