/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:20:04 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/11/02 01:57:40 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	open_map(char *path, t_game *game)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		end_game_with_message(game, "Map not found", 1);
	return (fd);
}

char	*split_line(char *line)
{
	char	*new_line;
	int		i;

	new_line = malloc(ft_strlen(line) * sizeof(char));
	if (!new_line)
		return (NULL);
	i = 0;
	while (line[i] != '\n')
	{
		new_line[i] = line[i];
		i++;
	}
	new_line[i] = '\0';
	free(line);
	return (new_line);
}

int	draw_map(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.height)
	{
		printf("%s\n", game->map.map[i]);
		i++;
	}
	printf("Player position: %f, %f\n", game->player.x, game->player.y);
	printf("Player angle: %f\n", game->player.angle);
	printf("Player tile position: %d, %d\n",
		game->player.tile_x, game->player.tile_y);
	printf("\n");
	return (0);
}
