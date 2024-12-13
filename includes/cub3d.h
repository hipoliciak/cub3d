/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:10:55 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/13 01:08:06 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "key_linux.h"
# include "libft.h"
# include "ft_printf.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>

// Macros

# define WIN_WIDTH 1200
# define WIN_HEIGHT 800
# define TEX_SIZE 64
# define MOVESPEED 0.0125
# define ROTSPEED 0.015

// Structures

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_tex
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				*floor;
	int				*ceiling;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	int				size;
	int				index;
	double			step;
	double			pos;
	int				x;
	int				y;
}	t_tex;

typedef struct s_map
{
	int		fd;
	int		line_count;
	char	*path;
	char	**file;
	int		height;
	int		width;
	int		index_end_of_map;
}	t_map;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	wall_dist;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_player
{
	char	dir;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		has_moved;
	int		move_x;
	int		move_y;
	int		rotate;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	t_map		map;
	char		**mapf;
	t_player	player;
	t_ray		ray;
	int			**texture_pixels;
	int			**textures;
	t_tex		texture;
}	t_game;

// Prototypes

// Init
void			init_game(t_game *game);
void			init_player(t_player *player);
void			init_map(t_map *map);
void			init_ray(t_ray *ray);
void			init_img_clean(t_img *img);
void			init_mlx(t_game *game);
void			init_img(t_game *game, t_img *image, int width, int height);
void			init_texture_img(t_game *game, t_img *image, char *path);
void			init_tex(t_tex *textures);
void			init_textures(t_game *game);
int				*xpm_to_img(t_game *game, char *path);

// Check file
int				is_cub_file(char *arg);
int				check_eof(t_map *map);
int				check_textures(t_tex *textures);
int				is_xpm_file(char *arg);
int				is_valid_rgb_range(int *rgb);

// Check map
int				check_map(t_game *game, char **mapf_tab);
int				check_map_top_bottom(char **mapf_tab, int i, int j);
int				check_map_borders(t_map *map, char **mapf_tab);
int				check_map_elements(t_game *game, char **mapf_tab);

// Init player
int				check_player_position(t_game *game, char **mapf_tab);
int				check_position_is_valid(t_game *game, char **mapf_tab);
void			init_player_north_south(t_player *player);
void			init_player_east_west(t_player *player);
void			init_player_dir(t_game *game);

// Get game
int				read_file(char *path, t_game *game);
void			fill_tab(int row, int column, int i, t_game *game);
int				get_number_of_lines(char *path);
int				parse_file(t_game *game, char **mapf);
int				process_line_content(t_game *game, char **mapf, int i, int j);
int				set_direction_textures(t_tex *textures, char *line, int j);
char			*get_texture_path(char *line, int j);
int				set_color_textures(t_tex *textures, char *line, int j);
int				*parse_rgb(char *line);
int				*convert_rgb(char **rgb_strings);
int				rgb_str_digits(char *str);
unsigned long	convert_rgb_to_hex(int *rgb_tab);
int				create_map(t_game *game, char **mapf, int i);

// Raycasting
int				raycasting(t_player *player, t_game *game);
void			init_raycasting_info(int x, t_ray *ray, t_player *player);
void			set_dda(t_ray *ray, t_player *player);
void			perform_dda(t_game *game, t_ray *ray);
void			calc_line_height(t_ray *ray, t_game *game, t_player *player);

// Render
int				render(t_game *game);
void			render_raycast(t_game *game);
void			render_frame(t_game *game);
void			set_frame_image_pixel(t_game *game, t_img *image, int x, int y);
void			set_image_pixel(t_img *image, int x, int y, int color);
void			update_tex_pixels(t_game *game, t_tex *tex, t_ray *ray, int x);
void			get_texture_index(t_game *game, t_ray *ray);
void			init_texture_pixels(t_game *game);

// Movement
int				move_player(t_game *game);
int				move_forward(t_game *game);
int				move_backward(t_game *game);
int				move_left(t_game *game);
int				move_right(t_game *game);
int				rotate(t_game *game, double rotdir);
int				validate_move(t_game *game, double new_x, double new_y);

// Utils
size_t			find_biggest_len(t_map *map, int i);
int				err(char *str, int code);
int				ft_isspace(int c);
int				ft_isspace_not_nl(int c);

// Exit
void			clean_exit(t_game *game, int code);
int				quit_cub3d(t_game *game);
void			free_tab(void **tab);
void			free_texture(t_tex *textures);
int				free_game(t_game *game);

#endif