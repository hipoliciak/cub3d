/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_game_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:07:16 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/15 17:24:22 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_map_lines(t_game *game, char **file, int i)
{
	int	index_value;
	int	j;

	index_value = i;
	while (file[i])
	{
		j = 0;
		while (ft_isspace_not_nl(file[i][j]))
			j++;
		if (file[i][j] != '1')
			break ;
		i++;
	}
	game->map.end_of_map = i;
	return (i - index_value);
}

int	fill_mapf_tab(t_map *map, char **mapf_tab, int index)
{
	int		i;
	int		j;

	map->width = find_biggest_len(map, index);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		mapf_tab[i] = malloc(sizeof(char) * (map->width + 1));
		if (!mapf_tab[i])
			return (err("Could not allocate memory", 1));
		while (map->file[index][j] && map->file[index][j] != '\n')
		{
			mapf_tab[i][j] = map->file[index][j];
			j++;
		}
		while (j < map->width)
			mapf_tab[i][j++] = '\0';
		i++;
		index++;
	}
	mapf_tab[i] = NULL;
	return (0);
}

void	change_space_into_wall(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->mapf[i])
	{
		j = 0;
		while (ft_isspace_not_nl(game->mapf[i][j]))
			j++;
		while (game->mapf[i][++j])
		{
			if (game->mapf[i][j] == ' '
				&& j != game->mapf[i][ft_strlen(game->mapf[i]) - 1])
				game->mapf[i][j] = '1';
		}
		i++;
	}
}

int	get_map_info(t_game *game, char **file, int i)
{
	game->map.height = count_map_lines(game, file, i);
	game->mapf = malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->mapf)
		return (err("Could not allocate memory", 1));
	if (fill_mapf_tab(&game->map, game->mapf, i))
		return (1);
	return (0);
}

int	create_map(t_game *game, char **file, int i)
{
	if (get_map_info(game, file, i))
		return (1);
	change_space_into_wall(game);
	return (0);
}
