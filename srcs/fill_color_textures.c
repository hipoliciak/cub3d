/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_color_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:07:47 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/11 01:18:30 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	has_only_non_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	*convert_and_validate_rgb(char **rgb_strings, int *rgb)
{
	int	i;

	i = -1;
	while (rgb_strings[++i])
	{
		rgb[i] = ft_atoi(rgb_strings[i]);
		if (rgb[i] == -1 || has_only_non_digits(rgb_strings[i]))
		{
			free_tab((void **)rgb_strings);
			free(rgb);
			return (0);
		}
	}
	free_tab((void **)rgb_strings);
	return (rgb);
}

static int	*set_rgb_colors(char *line)
{
	char	**rgb_to_convert;
	int		*rgb;
	int		count;

	rgb_to_convert = ft_split(line, ',');
	count = 0;
	while (rgb_to_convert[count])
		count++;
	if (count != 3)
	{
		free_tab((void **)rgb_to_convert);
		return (0);
	}
	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
	{
		err_msg(NULL, ERR_MALLOC, 0);
		return (0);
	}
	return (convert_and_validate_rgb(rgb_to_convert, rgb));
}

int	fill_color_textures(t_data *data, t_texinfo *textures, char *line, int j)
{
	if (line[j + 1] && ft_isprint(line[j + 1]) && line[j + 1] != ' ')
		return (err_msg(data->mapinfo.path, ERR_FLOOR_CEILING, ERR));
	if (!textures->ceiling && line[j] == 'C')
	{
		textures->ceiling = set_rgb_colors(line + j + 1);
		if (textures->ceiling == 0)
			return (err_msg(data->mapinfo.path, ERR_COLOR_CEILING, ERR));
	}
	else if (!textures->floor && line[j] == 'F')
	{
		textures->floor = set_rgb_colors(line + j + 1);
		if (textures->floor == 0)
			return (err_msg(data->mapinfo.path, ERR_COLOR_FLOOR, ERR));
	}
	else
		return (err_msg(data->mapinfo.path, ERR_FLOOR_CEILING, ERR));
	return (SUCCESS);
}
