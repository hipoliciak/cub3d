/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:07:39 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/13 01:04:53 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(void **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

void	free_texture(t_tex *textures)
{
	if (textures->north)
		free(textures->north);
	if (textures->south)
		free(textures->south);
	if (textures->west)
		free(textures->west);
	if (textures->east)
		free(textures->east);
	if (textures->floor)
		free(textures->floor);
	if (textures->ceiling)
		free(textures->ceiling);
}

int	free_game(t_game *game)
{
	if (game->textures)
		free_tab((void **)game->textures);
	if (game->texture_pixels)
		free_tab((void **)game->texture_pixels);
	if (game->map.fd > 0)
		close(game->map.fd);
	if (game->map.file)
		free_tab((void **)game->map.file);
	if (game->mapf)
		free_tab((void **)game->mapf);
	free_texture(&game->texture);
	return (1);
}

void	clean_exit(t_game *game, int code)
{
	if (!game)
		exit(code);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		mlx_loop_end(game->mlx);
		free(game->mlx);
	}
	free_game(game);
	exit(code);
}

int	quit_cub3d(t_game *game)
{
	clean_exit(game, 0);
	return (0);
}
