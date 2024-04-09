/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:40:26 by emichels          #+#    #+#             */
/*   Updated: 2024/04/09 16:50:45 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_hook(void *param)
{
	mlx_t	*mlx = param;
	
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

int32_t	main(int argc, char **argv)
{
	int     fd;
	char    *map_str;
	t_map   map;
	
	if (argc == 2)
	{
		valid_extension(argv[1]);
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			error_msg("Error\nFile open error\n", NULL, NULL);
		map_str = read_map(fd);
		// printf("%s\n", map_str);
		map = set_map_limits(map_str);
		is_valid_character(map_str);
		is_rectangle(map, map_str);
		mlx_set_setting(MLX_MAXIMIZED, true);
		mlx_t	*mlx = mlx_init(WIDTH, HEIGHT, "title", false);
		if (!mlx)
			error_msg((char *)mlx_strerror(mlx_errno), NULL, NULL);
// TEXTURES
		int				i;
		mlx_texture_t	*wall;
		mlx_texture_t	*floor;
		mlx_texture_t	*player;
		mlx_texture_t	*collect;
		mlx_texture_t	*door_clo;
		mlx_image_t		*w_img;
		mlx_image_t		*f_img;
		mlx_image_t		*p_img;
		mlx_image_t		*c_img;
		mlx_image_t		*d_img;
		wall = mlx_load_png("./textures/wall.png");
		floor = mlx_load_png("./textures/floor.png");
		player = mlx_load_png("./textures/player.png");
		collect = mlx_load_png("./textures/collect.png");
		door_clo = mlx_load_png("./textures/door_closed.png");
		
		if (!wall || !floor)
			error_msg((char *)mlx_strerror(mlx_errno), NULL, NULL);
		w_img = mlx_texture_to_image(mlx, wall);
		f_img = mlx_texture_to_image(mlx, floor);
		p_img = mlx_texture_to_image(mlx, player);
		c_img = mlx_texture_to_image(mlx, collect);
		d_img = mlx_texture_to_image(mlx, door_clo);
		if (!w_img || !f_img)
			error_msg((char *)mlx_strerror(mlx_errno), NULL, NULL);
		i = 0;
		map.y = 0;
		map.x = 0;
		while (map_str[i])
		{
			if (map_str[i] == '1')
			{
				if (mlx_image_to_window(mlx, w_img, map.x * IMGSIZE, map.y * IMGSIZE) < 0)
					error_msg((char *)mlx_strerror(mlx_errno), NULL, NULL);
				if (map.x == map.max_x)
				{
					map.y++;
					map.x = 0;
				}
				else
					map.x++;
			}
			else if (map_str[i] == '0')
			{
				if (mlx_image_to_window(mlx, f_img, map.x * IMGSIZE, map.y * IMGSIZE) < 0)
					error_msg((char *)mlx_strerror(mlx_errno), NULL, NULL);
				map.x++;
			}
			else if (map_str[i] == 'P')
			{
				if (mlx_image_to_window(mlx, p_img, map.x * IMGSIZE, map.y * IMGSIZE) < 0)
					error_msg((char *)mlx_strerror(mlx_errno), NULL, NULL);
				map.x++;
			}
			else if (map_str[i] == 'C')
			{
				if (mlx_image_to_window(mlx, c_img, map.x * IMGSIZE, map.y * IMGSIZE) < 0)
					error_msg((char *)mlx_strerror(mlx_errno), NULL, NULL);
				map.x++;
			}
			else if (map_str[i] == 'E')
			{
				if (mlx_image_to_window(mlx, d_img, map.x * IMGSIZE, map.y * IMGSIZE) < 0)
					error_msg((char *)mlx_strerror(mlx_errno), NULL, NULL);
				map.x++;
			}
			i++;
		}
// TEXTURES
		mlx_loop_hook(mlx, ft_hook, mlx);
		mlx_loop(mlx);
		mlx_terminate(mlx);
		// printf("max x: %i\n", map.max_x);
		// printf("max y: %i\n", map.max_y);
		// printf("collectibles: %i\n", map.collect_n);
		//free(map_str); // this might not be necessary, keeping it here just for leak checking
	}
	return (0);
}
