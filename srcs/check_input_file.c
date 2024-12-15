/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:06:35 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/15 17:24:16 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_cub_file(char *arg)
{
	int	ret;

	if (!arg || ft_strlen(arg) < 4)
		return (0);
	ret = ft_strncmp(&arg[ft_strlen(arg) - 4], ".cub", 4);
	if (ret != 0)
		return (1);
	return (0);
}

int	is_xpm_file(char *arg)
{
	int	ret;

	if (!arg || ft_strlen(arg) < 4)
		return (0);
	ret = ft_strncmp(&arg[ft_strlen(arg) - 4], ".xpm", 4);
	if (ret == 0)
		return (1);
	return (0);
}

int	check_textures(t_tex *textures)
{
	if (!textures->north || !textures->south || !textures->west
		|| !textures->east)
		return (err("Missing texture(s)", 1));
	if (!textures->floor || !textures->ceiling)
		return (err("Missing color(s)", 1));
	if (!is_xpm_file(textures->north) || !is_xpm_file(textures->south)
		|| !is_xpm_file(textures->west) || !is_xpm_file(textures->east))
		return (err("Texture not .xpm", 1));
	return (0);
}

int	check_eof(t_map *map)
{
	int	i;
	int	j;

	i = map->end_of_map;
	while (map->file[i])
	{
		j = 0;
		while (map->file[i][j])
		{
			if (ft_isspace(map->file[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
