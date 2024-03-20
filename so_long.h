/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:08:40 by emichels          #+#    #+#             */
/*   Updated: 2024/03/20 16:27:42 by emichels         ###   ########.fr       */
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
# include <stdio.h> // for printf testing, remove

# define BUFFERSIZE 25

typedef struct s_map
{
	int	y;
	int	x;
	int	max_y;
	int max_x;
}	t_map;

char	*read_map(int fd);
t_map	set_map_limits(char *map_str);
void	is_rectangle(t_map map, char *map_str);

void	error_msg(char *msg, int code);



#endif
