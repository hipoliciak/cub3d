/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:09:51 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/11 00:05:47 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_move(t_data *data, double new_x, double new_y)
{
	int	moved;

	moved = 0;
	if (data->map[(int)new_y][(int)new_x] == '0')
	{
		data->player.pos_x = new_x;
		data->player.pos_y = new_y;
		moved = 1;
	}
	return (moved);
}

int	move_player(t_data *data)
{
	int	moved;

	moved = 0;
	if (data->player.move_y == 1)
		moved += move_forward(data);
	if (data->player.move_y == -1)
		moved += move_backward(data);
	if (data->player.move_x == -1)
		moved += move_left(data);
	if (data->player.move_x == 1)
		moved += move_right(data);
	if (data->player.rotate != 0)
		moved += rotate(data, data->player.rotate);
	return (moved);
}
