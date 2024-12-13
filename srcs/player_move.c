/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:09:51 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/13 01:04:53 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_move(t_game *game, double new_x, double new_y)
{
	int	moved;

	moved = 0;
	if (game->mapf[(int)new_y][(int)new_x] == '0')
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
		moved = 1;
	}
	return (moved);
}

int	move_player(t_game *game)
{
	int	moved;

	moved = 0;
	if (game->player.move_y == 1)
		moved += move_forward(game);
	if (game->player.move_y == -1)
		moved += move_backward(game);
	if (game->player.move_x == -1)
		moved += move_left(game);
	if (game->player.move_x == 1)
		moved += move_right(game);
	if (game->player.rotate != 0)
		moved += rotate(game, game->player.rotate);
	return (moved);
}
