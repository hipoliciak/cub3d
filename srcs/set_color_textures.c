/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:07:47 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/13 00:35:02 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_str_digits(char *rgb_string)
{
	int	i;

	i = 0;
	while (rgb_string[i])
	{
		if (ft_isdigit(rgb_string[i]))
			return (0);
		i++;
	}
	return (1);
}

unsigned long	convert_rgb_to_hex(int *rgb_tab)
{
	int	r;
	int	g;
	int	b;

	if (!rgb_tab)
		return (err("Could not convert RGB to hex", 0));
	r = rgb_tab[0] & 0xff;
	g = rgb_tab[1] & 0xff;
	b = rgb_tab[2] & 0xff;
	return ((r << 16) | (g << 8) | b);
}

int	*convert_rgb(char **rgb_strings)
{
	int	i;
	int	*rgb;

	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
	{
		err("Could not allocate memory", 0);
		return (0);
	}
	i = 0;
	while (rgb_strings[i])
	{
		rgb[i] = ft_atoi(rgb_strings[i]);
		if (rgb[i] == -1 || rgb_str_digits(rgb_strings[i]))
		{
			free_tab((void **)rgb_strings);
			free(rgb);
			return (0);
		}
		i++;
	}
	free_tab((void **)rgb_strings);
	return (rgb);
}

int	*parse_rgb(char *line)
{
	char	**rgb_strings;
	int		count;

	count = 0;
	rgb_strings = ft_split(line, ',');
	while (rgb_strings && rgb_strings[count])
		count++;
	if (count != 3)
	{
		free_tab((void **)rgb_strings);
		return (0);
	}
	return (convert_rgb(rgb_strings));
}

int	set_color_textures(t_tex *textures, char *line, int j)
{
	if (line[j + 1] && ft_isprint(line[j + 1]) && line[j + 1] != ' ')
		return (err("Invalid floor/ceiling color", 2));
	if (!textures->ceiling && line[j] == 'C')
	{
		textures->ceiling = parse_rgb(line + j + 1);
		if (!textures->ceiling)
			return (err("Invalid ceiling color", 2));
		else
			textures->hex_ceiling = convert_rgb_to_hex(textures->ceiling);
	}
	else if (!textures->floor && line[j] == 'F')
	{
		textures->floor = parse_rgb(line + j + 1);
		if (!textures->floor)
			return (err("Invalid floor color", 2));
		else
			textures->hex_floor = convert_rgb_to_hex(textures->floor);
	}
	else
		return (err("Invalid floor/ceiling color", 2));
	return (0);
}
