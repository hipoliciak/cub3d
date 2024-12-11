/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:06:35 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/10 23:57:43 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_cub_file(char *arg)
{
	int	ret;

	if (!arg || ft_strlen(arg) < 4)
		return (0);
	ret = ft_strncmp(&arg[ft_strlen(arg) - 4], ".cub", 4);
	if (ret == 0)
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
