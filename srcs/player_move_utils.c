/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:09:45 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/13 00:42:25 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.dir_x * MOVESPEED;
	new_y = game->player.pos_y + game->player.dir_y * MOVESPEED;
	return (validate_move(game, new_x, new_y));
}

int	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.dir_x * MOVESPEED;
	new_y = game->player.pos_y - game->player.dir_y * MOVESPEED;
	return (validate_move(game, new_x, new_y));
}

int	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.dir_y * MOVESPEED;
	new_y = game->player.pos_y - game->player.dir_x * MOVESPEED;
	return (validate_move(game, new_x, new_y));
}

int	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.dir_y * MOVESPEED;
	new_y = game->player.pos_y + game->player.dir_x * MOVESPEED;
	return (validate_move(game, new_x, new_y));
}

int	rotate(t_game *game, double rotdir)
{
	t_player	*p;
	double		rotspeed;
	double		tmp_x;

	if (!game)
		return (0);
	p = &game->player;
	rotspeed = ROTSPEED * rotdir;
	tmp_x = p->dir_x;
	p->dir_x = p->dir_x * cos(rotspeed) - p->dir_y * sin(rotspeed);
	p->dir_y = tmp_x * sin(rotspeed) + p->dir_y * cos(rotspeed);
	tmp_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rotspeed) - p->plane_y * sin(rotspeed);
	p->plane_y = tmp_x * sin(rotspeed) + p->plane_y * cos(rotspeed);
	return (1);
}
