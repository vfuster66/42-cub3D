/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecullier <ecullier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 09:16:25 by vfuster-          #+#    #+#             */
/*   Updated: 2023/12/12 21:20:24 by ecullier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <fcntl.h>
# include <limits.h>
# include <unistd.h>
# include <ctype.h>
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "../libft/includes/libft.h"
# include "../mlx_linux/mlx.h"

# define MAX_WIDTH 620
# define MAX_HEIGHT 480
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64
# define CELL_SIZE 10
# define BUFFER_SIZE 1024

# define RESET "0xff0000"

# define ERR_MLX_START "Could not start mlx"
# define ERR_MLX_WIN "Could not create mlx window"
# define ERR_MLX_IMG "Could not create mlx image"

# define KeyPress 2
# define KeyPressMask (1L<<0)

/*---------- STRUCTURES ----------*/

typedef enum e_key_code
{
	CLOSE_ICON = 17,
	ESC_KEY = 65307,
	KEY_PRESS = 2,
	KEY_RELEASE = 3,
	UP_KEY = 65362,
	DOWN_KEY = 65364,
	LEFT_KEY = 65363,
	RIGHT_KEY = 65361,
	W_KEY = 119,
	A_KEY = 97,
	S_KEY = 115,
	D_KEY = 100
}	t_key_code;

typedef struct s_key_state {
	bool W;
	bool S;
	bool A;
	bool D;
} t_key_state;

extern t_key_state g_keystate;

// Texture
typedef struct s_texture
{
	void	*img;
	char	*path;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_texture;

// Raycast
typedef struct s_ray
{
	t_texture	*wall_texture;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			tex_x;
}				t_ray;

// Window
typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*title;
	char	*addr;
	int		endian;
	int		bits_per_pixel;
	int		line_length;
	int		win_width;
	int		win_height;
}				t_mlx;

// Image
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

// Map
typedef struct s_map
{
	char		*north_texture_path;
	char		*south_texture_path;
	char		*west_texture_path;
	char		*east_texture_path;
	t_texture	north_texture;
	t_texture	south_texture;
	t_texture	east_texture;
	t_texture	west_texture;
	t_mlx		*mlx_ref;
	int			width;
	int			height;
	char		**map;
	int			start_x;
	int			start_y;
	int			player_x;
	int			player_y;
	int			player_direction;
	bool		floor_color_set;
	bool		ceiling_color_set;
	int			ceiling_color[3];
	int			floor_color[3];
	bool		config_done;
	char*		resolution_str;
	int			map_height;
	int allocated_lines;
}				t_map;

// Player
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}				t_player;

// Data
typedef struct s_data
{
	t_mlx		*mlx;
	t_map       *map;
	t_player    *player;
	t_img		*img;
}				t_data;

typedef struct s_game_context
{
	t_data		*data;
	t_mlx		*mlx_info;
	t_map		*map_info;
	t_player	*player;
}				t_game_context;

typedef struct s_line {
    char *line;
    struct s_line *next;
} t_line;

/*---------- FONCTIONS ----------*/
// Parsing Config
int			validate_resolution(const char *resolution_str);
int			validate_rgb(const char *rgb_str, int *rgb_arr);
int			validate_texture_path(const char *path);
int			handle_texture_and_color(char *key, char *value, t_map *map_info);
int			parse_config_line(char* line, t_map *map_info);
int			read_and_split_lines(int fd, char **line, char **saveptr, int *config_completed);
int			process_lines(int fd, t_map *map_info);
int			parse_config_file(const char* file_path, t_map *map_info);
// Parsing Map
int			is_wall_line(const char* line);
int			process_player_position(char *line, t_map *map_info, int line_number);
int			parse_map_line(char* line, t_map *map_info, int line_number);
ssize_t		read_file_to_buffer(int fd, char *buffer, size_t buffer_size);
int			handle_map_line(char *line, t_map *map_info, int *start_reading_map, int *line_number);
int			process_map_lines(char *buffer, t_map *map_info, int *start_reading_map, int *line_number);
int			open_file_for_parsing(const char *file_path);
int			parse_map(const char* file_path, t_map *map_info);
int			parse_file(const char* file_path, t_map *map_info);
int check_map_is_at_the_end(t_map *map_info);
bool is_valid_map_position(char c);
int check_player_position_is_valid(t_map *map_info);
int check_file(char *arg, bool cub);
int check_map_elements(t_map *map_info);

/*-----------------------------------------------------------*/
// Check
int			check_file_accessibility(const char *filename);
int			check_arguments(int ac, char **av);
int			is_valid_character(char c);
int			validate_single_map_line(char *line, int line_number,
				int height, int *player_start_count);
int			validate_map(t_map *map_info);
/*----------------------------------------------------------*/
// Window
int			close_window(t_data *data);
int			keyboard_actions(int key, t_data *data);
void		set_window(t_data *data);
/*----------------------------------------------------------*/
// Init
void		initialize_player(t_player *player);
void		init_player(t_player *player, t_map *map_info);
void		init_ray(t_ray *ray);
void		init_img_clean(t_mlx *mlx);
bool		init_texture(void *mlx, t_texture *texture, char *path);
void		init_img(t_data *data, void *mlx, int width, int height);
bool		init_texture(void *mlx, t_texture *texture, char *file_path);
bool		init_all_textures(t_mlx *mlx_info, t_map *map_info);
int		is_player_inside_map(t_player *player, t_map *map);
/*----------------------------------------------------------*/
// Moves
void		move_forward(t_player *player, double move_speed);
void		move_backward(t_player *player, double move_speed);
void		rotate_right(t_player *player, double rot_speed);
void		rotate_left(t_player *player, double rot_speed);
void		move_left(t_player *player, double move_speed);
void		move_right(t_player *player, double move_speed);
int			handle_input(int keycode, t_data *data);
/*----------------------------------------------------------*/
// Raycast
void		calculate_ray_and_deltadist(t_data *data, t_ray *ray, int x);
void		calculate_step_and_sidedist(t_data *data, t_ray *ray);
void		calculate_dist(t_data *data, t_ray *ray);
int			calculate_height_wall(t_data *data, t_ray *ray);
void		cast_ray(t_data *data, t_ray *ray, int x);
/*----------------------------------------------------------*/
// Clean
void		clean_exit(t_mlx *mlx, t_map *map);
void		cleanup(t_map *map_info, t_mlx *mlx_info);
void		clean_textures(t_map *map);
/*----------------------------------------------------------*/
// Free
void		free_texture_paths(t_map *map_info);
void		free_map_lines(t_map *map_info);
void		free_map(t_map *map_info);
/*----------------------------------------------------------*/
// Error
int			err_msg(char *detail, char *str, int code);
int			err_msg_val(int detail, char *str, int code);
/*----------------------------------------------------------*/
// Principal
int			init_mlx_and_window(t_mlx *mlx_info);
bool		check_wall(t_map *map_info, int x, int y);
void		update_game(t_data *data, t_player *player);
/*----------------------------------------------------------*/
// Draw
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
bool		init_texture(void *mlx, t_texture *texture, char *file_path);
bool		init_all_textures(t_mlx *mlx_info, t_map *map_info);
void		draw_floor(t_data *data);
void		draw_ceiling(t_data *data);
void		draw_walls(t_data *data, t_ray *ray, int x);
void		render(t_data *data);

#endif