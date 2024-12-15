/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:08:02 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/15 02:19:58 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_texture_pixels(t_game *game)
{
	int	i;

	if (game->texture_pixels)
		free_tab((void **)game->texture_pixels);
	game->texture_pixels = ft_calloc(game->win_height + 1,
			sizeof * game->texture_pixels);
	if (!game->texture_pixels)
		clean_exit(game, err("Could not allocate memory", 1));
	i = 0;
	while (i < game->win_height)
	{
		game->texture_pixels[i] = ft_calloc(game->win_width + 1,
				sizeof * game->texture_pixels);
		if (!game->texture_pixels[i])
			clean_exit(game, err("Could not allocate memory", 1));
		i++;
	}
}

int	get_texture_index(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			return (3);
		else
			return (2);
	}
	else
	{
		if (ray->dir_y > 0)
			return (1);
		else
			return (0);
	}
}

void	update_tex_pixels(t_game *game, t_tex *tex, t_ray *ray, int x)
{
	int	y;
	int	color;
	int	tex_index;

	tex_index = get_texture_index(ray);
	tex->x = (int)(ray->wall_x * tex->size);
	if ((ray->side == 0 && ray->dir_x < 0)
		|| (ray->side == 1 && ray->dir_y > 0))
		tex->x = tex->size - tex->x - 1;
	tex->step = 1.0 * tex->size / ray->line_height;
	tex->pos = (ray->draw_start - game->win_height / 2
			+ ray->line_height / 2) * tex->step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex->y = (int)tex->pos & (tex->size - 1);
		tex->pos += tex->step;
		color = game->textures[tex_index][tex->size * tex->y + tex->x];
		if (color > 0)
			game->texture_pixels[y][x] = color;
		y++;
	}
}
