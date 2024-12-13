/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:10:25 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/13 00:42:25 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->size_line / 4) + x;
	image->addr[pixel] = color;
}

void	set_frame_image_pixel(t_game *game, t_img *image, int x, int y)
{
	if (game->texture_pixels[y][x] > 0)
		set_image_pixel(image, x, y, game->texture_pixels[y][x]);
	else if (y < game->win_height / 2)
		set_image_pixel(image, x, y, game->texture.hex_ceiling);
	else if (y < game->win_height -1)
		set_image_pixel(image, x, y, game->texture.hex_floor);
}

void	render_frame(t_game *game)
{
	t_img	image;
	int		x;
	int		y;

	image.img = NULL;
	init_img(game, &image, game->win_width, game->win_height);
	y = 0;
	while (y < game->win_height)
	{
		x = 0;
		while (x < game->win_width)
		{
			set_frame_image_pixel(game, &image, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, image.img, 0, 0);
	mlx_destroy_image(game->mlx, image.img);
}

void	render_raycast(t_game *game)
{
	init_texture_pixels(game);
	init_ray(&game->ray);
	raycasting(&game->player, game);
	render_frame(game);
}

int	render(t_game *game)
{
	game->player.has_moved += move_player(game);
	if (game->player.has_moved == 0)
	{
		render_frame(game);
		return (0);
	}
	render_raycast(game);
	return (0);
}
