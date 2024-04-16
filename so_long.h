/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:08:40 by emichels          #+#    #+#             */
/*   Updated: 2024/04/16 13:28:48 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <stdbool.h>
# include "libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define BUFFERSIZE 25
# define WIDTH 48
# define HEIGHT 48

typedef struct s_texture
{
	mlx_texture_t	*wall;
	mlx_texture_t	*floor;
	mlx_texture_t	*player;
	mlx_texture_t	*collect;
	mlx_texture_t	*door_clo;
	mlx_texture_t	*door_opn;
}	t_texture;

typedef struct s_image
{
	mlx_image_t		*w_img;
	mlx_image_t		*f_img;
	mlx_image_t		*p_img;
	mlx_image_t		*c_img;
	mlx_image_t		*dc_img;
	mlx_image_t		*do_img;
}	t_image;

typedef struct s_map
{
	int		fd;
	mlx_t	*mlx;
	int		y;
	int		x;
	int		max_y;
	int		max_x;
	int		collect_n;
	int		steps;
	int		plr_y;
	int		plr_x;
	char	*str;
	char	**arr;
	t_image	*images;
}	t_map;

// error handling
void	struct_error(char *msg, t_map *map);
void	texture_error(char *msg, t_map *map, t_texture *textures);
void	free_textures(t_texture *textures);
void	free_images(t_map *map);

// player movement & status
void	wasd_keyhook(mlx_key_data_t keydata, void *param);
void	count_steps(t_map *map);
void	count_collectibles(t_map *map);
void	exit_open(t_map *map);

// display
void	resize_images(t_map *map);
void	load_textures(t_map *map);
void	load_images(t_map *map, t_texture *textures);
void	display_map(t_map *map);

// map handling
void	read_map(t_map *map);
void	valid_extension(char *str);
void	set_map_limits(t_map *map);
void	is_rectangle(t_map *map);
void	is_valid_character(t_map *map);
void	traverse_path(char **arr, t_map *cur, int y, int x);

#endif
