/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:06 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/29 00:35:03 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "ft_printf.h"
# include "mlx.h"
# include "key_linux.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

// Macros
# define WIN_WIDTH 1200
# define WIN_HEIGHT 800
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define MOVESPEED 0.05
# define ROTSPEED 0.02
# define MINIMAP_TILE_SIZE 10
# define MINIMAP_WALL_COLOR 0xFFFFFF
# define MINIMAP_FLOOR_COLOR 0x000000
# define MINIMAP_PLAYER_COLOR 0xFF0000

// Structs
typedef struct s_image
{
	void		*img;
	int			*addr;
	int			pixel_bits;
	int			size_line;
	int			endian;
}	t_image;

typedef struct s_file
{
	char		**file;
	char		**map;
	int			map_start;
	int			map_height;
	int			player_count;
	char		*north_path;
	char		*south_path;
	char		*west_path;
	char		*east_path;
	int			*rgb_floor;
	int			*rgb_ceiling;
}	t_file;

typedef struct s_ray
{
	double		dir_x;
	double		dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			map_x;
	int			map_y;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
}	t_ray;

typedef struct s_player
{
	char		dir;
	double		dir_x;
	double		dir_y;
	double		pos_x;
	double		pos_y;
	double		plane_x;
	double		plane_y;
	int			key_state[6];
}	t_player;

typedef struct s_game
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				win_width;
	int				win_height;
	t_file			file;
	t_player		player;
	int				texture_width;
	int				texture_height;
	int				*north_texture;
	int				*south_texture;
	int				*west_texture;
	int				*east_texture;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	t_image			frame;
}	t_game;

// Init
void			init_game(t_game *game);
void			init_player(t_player *player);
void			init_file(t_file *file);
void			init_image(t_image *image);

// Get game info
int				copy_file(t_game *game, char *path);
int				fill_file(t_game *game, int fd);
int				get_number_of_lines(char *path);
int				parse_file(t_game *game);
int				parse_line(t_game *game, char *line, int i);
int				set_direction_textures(t_file *file, char *line, int j);
char			*get_texture_path(char *line, int j);
int				set_color_textures(t_file *file, char *line, int j);
int				*parse_rgb(char *line);
int				check_rgb_strings(char **rgb_strings, int count);
int				rgb_str_digits(char *str);
int				*convert_rgb_to_int(char **rgb_strings);
int				copy_map(t_game *game);
int				count_map_lines(char **file, int map_start);

// Check file
int				is_cub_file(char *arg);
int				check_textures(t_game *game);
int				is_xpm_file(char *arg);

// Check map
int				check_map(t_game *game);
int				check_map_end(char **map, int map_length);
int				check_map_content(char **map);
int				check_map_top_bottom(char **map, int i, int j);
int				check_map_inside(char **map, int i, int j, int k);

// Init player
int				check_player_position(t_game *game, char **map);
void			init_player_north_south(t_player *player);
void			init_player_east_west(t_player *player);

// Graphics
void			create_textures(t_game *game);
int				*load_texture(t_game *game, char *path);
int				*copy_texture_to_buffer(t_game *game, t_image *img);
unsigned long	convert_rgb_to_hex(int *rgb);

// Engine
int				move_player(t_game *game);
void			try_move(t_game *game, double new_x, double new_y);
void			rotate_player(t_player *p, double angle);

// Render
int				render_game(t_game *game);
void			render_frame(t_game *game);
void			fill_ceiling_and_floor(t_game *game);
void			render_walls(t_game *game);
void			render_column(t_game *game, int x, t_ray ray, int tex_x);
void			init_ray(t_game *game, t_ray *ray);
void			calculate_ray_direction(t_game *game, t_ray *ray, int x);
void			calculate_step_and_side_dist(t_game *game, t_ray *ray);
void			perform_dda(t_game *game, t_ray *ray);
void			calculate_wall_and_tex(t_game *game, t_ray *ray, int *tex_x);
void			render_minimap(t_game *game);
void			draw_tile(t_game *game, int screen_x, int screen_y, int color);
int				get_tile_color(char tile);

// Utils
int				err(char *str, int code);
int				is_space(int c);
int				is_surrounded_by_space_or_wall(char **map, int i, int j);

// End
void			clean_exit(t_game *game, int code);
int				end_game(t_game *game);
void			free_tab(void **tab);
void			free_textures_info(t_file *file);
int				free_game(t_game *game);

// Debug
int				draw_map(t_game *game);

#endif