/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:08:40 by emichels          #+#    #+#             */
/*   Updated: 2024/04/09 17:12:51 by emichels         ###   ########.fr       */
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
# define WIDTH 640
# define HEIGHT 640
# define IMGSIZE 12

typedef struct s_map
{
	int		y;
	int		x;
	int		max_y;
	int 	max_x;
	int		collect_n;
}	t_map;

char	*read_map(int fd);
void	valid_extension(char *str);
t_map	set_map_limits(char *map_str);
void	is_rectangle(t_map map, char *map_str);
void	is_valid_character(char *map_str);
void	traverse_path(char **map_arr, t_map cur, int y, int x);

void	error_msg(char *msg, char *str, char **arr);



#endif
