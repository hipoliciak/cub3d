/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:07:05 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/11 01:02:30 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_valid_rgb(int *rgb)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			tmp = ft_itoa(rgb[i]);
			err_msg(tmp, ERR_TEX_RGB_VAL, FAILURE);
			free(tmp);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

static unsigned long	convert_rgb_to_hex(int *rgb_tab)
{
	unsigned long	result;
	int				r;
	int				g;
	int				b;

	r = rgb_tab[0];
	g = rgb_tab[1];
	b = rgb_tab[2];
	result = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (result);
}

int	check_textures_validity(t_data *data, t_texinfo *textures)
{
	if (!textures->north || !textures->south || !textures->west
		|| !textures->east)
		return (err_msg(data->mapinfo.path, ERR_TEX_MISSING, FAILURE));
	if (!textures->floor || !textures->ceiling)
		return (err_msg(data->mapinfo.path, ERR_COLOR_MISSING, FAILURE));
	if (!is_xpm_file(textures->north)
		|| !is_xpm_file(textures->south)
		|| !is_xpm_file(textures->west)
		|| !is_xpm_file(textures->east))
		return (FAILURE);
	if (check_valid_rgb(textures->floor) == FAILURE
		|| check_valid_rgb(textures->ceiling) == FAILURE)
		return (FAILURE);
	textures->hex_floor = convert_rgb_to_hex(textures->floor);
	textures->hex_ceiling = convert_rgb_to_hex(textures->ceiling);
	return (SUCCESS);
}
