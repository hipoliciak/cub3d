/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:08:52 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/11 00:39:50 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	key_press_handler(int key, t_data *data)
{
	if (key == CLOSE_BTN || key == KEY_ESC || key == KEY_Q)
		quit_cub3d(data);
	if (key == KEY_AR_L)
		data->player.rotate -= 1;
	if (key == KEY_AR_R)
		data->player.rotate += 1;
	if (key == KEY_W)
		data->player.move_y = 1;
	if (key == KEY_A)
		data->player.move_x = -1;
	if (key == KEY_S)
		data->player.move_y = -1;
	if (key == KEY_D)
		data->player.move_x = 1;
	return (0);
}

static int	key_release_handler(int key, t_data *data)
{
	if (key == CLOSE_BTN || key == KEY_ESC || key == KEY_Q)
		quit_cub3d(data);
	if (key == KEY_W && data->player.move_y == 1)
		data->player.move_y = 0;
	if (key == KEY_S && data->player.move_y == -1)
		data->player.move_y = 0;
	if (key == KEY_A && data->player.move_x == -1)
		data->player.move_x += 1;
	if (key == KEY_D && data->player.move_x == 1)
		data->player.move_x -= 1;
	if (key == KEY_AR_L && data->player.rotate <= 1)
		data->player.rotate = 0;
	if (key == KEY_AR_R && data->player.rotate >= -1)
		data->player.rotate = 0;
	return (0);
}

static int	parse_args(t_data *data, char **av)
{
	if (!is_cub_file(av[1]))
	{
		err_msg(av[1], ERR_FILE_NOT_CUB, 1);
		return (1);
	}
	parse_data(av[1], data);
	if (get_file_data(data, data->mapinfo.file) == FAILURE)
		return (free_data(data));
	if (check_map_validity(data, data->map) == FAILURE)
		return (free_data(data));
	if (check_textures_validity(data, &data->texinfo) == FAILURE)
		return (free_data(data));
	init_player_direction(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (err_msg("Usage", ERR_USAGE, 1));
	init_data(&data);
	if (parse_args(&data, av) != 0)
		return (1);
	init_mlx(&data);
	init_textures(&data);
	render_raycast(&data);
	// render(&data);
	mlx_hook(data.win, KEY_PRESS, KEY_PRESS_MASK, key_press_handler, &data);
	mlx_hook(data.win, KEY_RELEASE, KEY_RELEASE_MASK, key_release_handler, &data);
	mlx_hook(data.win, CLOSE_BTN, NO_EVENT_MASK, quit_cub3d, &data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	return (0);
}
