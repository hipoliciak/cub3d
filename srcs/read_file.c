/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:09:24 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/13 00:42:25 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_number_of_lines(char *path)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	else
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			line_count++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (line_count);
}

void	fill_tab(int row, int column, int i, t_game *game)
{
	char	*line;

	line = get_next_line(game->map.fd);
	while (line != NULL)
	{
		game->map.file[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!game->map.file[row])
		{
			err("Could not allocate memory", 1);
			return (free_tab((void **)game->map.file));
		}
		while (line[i] != '\0')
			game->map.file[row][column++] = line[i++];
		game->map.file[row++][column] = '\0';
		column = 0;
		i = 0;
		free(line);
		line = get_next_line(game->map.fd);
	}
	game->map.file[row] = NULL;
}

int	read_file(char *path, t_game *game)
{
	int		row;
	int		i;
	size_t	column;

	i = 0;
	row = 0;
	column = 0;
	game->map.line_count = get_number_of_lines(path);
	game->map.path = path;
	game->map.file = ft_calloc(game->map.line_count + 1, sizeof(char *));
	if (!(game->map.file))
		return (err("Could not allocate memory", 1));
	game->map.fd = open(path, O_RDONLY);
	if (game->map.fd < 0)
	{
		free_tab((void **)game->map.file);
		return (1);
	}
	else
	{
		fill_tab(row, column, i, game);
		close(game->map.fd);
	}
	return (0);
}
