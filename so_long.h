/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:08:40 by emichels          #+#    #+#             */
/*   Updated: 2024/04/10 15:45:36 by emichels         ###   ########.fr       */
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
# include <stdio.h> // for printf testing, remove maybe

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
	mlx_t	*mlx;
	int		y;
	int		x;
	int		max_y;
	int 	max_x;
	int		collect_n;
	int		steps;
	int		plr_y;
	int		plr_x;
	char	**arr;
	t_image	*images;
}	t_map;

void	error_msg(char *msg, char *str, char **arr);

char	*read_map(int fd);
void	valid_extension(char *str);
t_map	set_map_limits(char *map_str);
void	is_rectangle(t_map map, char *map_str);
void	is_valid_character(char *map_str);
void	traverse_path(char **map_arr, t_map cur, int y, int x);




#endif
