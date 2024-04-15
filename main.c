/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:40:26 by emichels          #+#    #+#             */
/*   Updated: 2024/04/15 15:55:32 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_map_struct(t_map *map)
{
	map->mlx = NULL;
	map->y = 0;
	map->x = 0;
	map->max_y = 0;
	map->max_x = 0;
	map->collect_n = 0;
	map->steps = 0;
	map->plr_y = 0;
	map->plr_x = 0;
	map->str = NULL;
	map->arr = NULL;
	map->images = NULL;
}

int32_t	main(int argc, char **argv)
{
	int     fd;
	t_map   map;
	
	if (argc == 2)
	{
		init_map_struct(&map);
		valid_extension(argv[1]);
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			struct_error("Error\nfile open error\n", &map);
		map.str = read_map(fd);
		set_map_limits(&map);
		is_valid_character(&map);
		is_rectangle(&map);
		map.arr = ft_split(map.str, '\n');
		if (!map.arr)
			struct_error("Error\nstring split failed\n", &map);
		mlx_set_setting(MLX_STRETCH_IMAGE, true);
		map.mlx = mlx_init((map.max_x + 1) * WIDTH, (map.max_y + 1) * HEIGHT, "so long", true);
		if (!map.mlx)
			struct_error((char *)mlx_strerror(mlx_errno), &map);
		display_map(&map);
		display_player(&map);
		mlx_key_hook(map.mlx, &wasd_keyhook, &map);
		mlx_loop(map.mlx);
		mlx_terminate(map.mlx);
		free(map.str);
		ft_free(map.arr);
		free_images(&map);
	}
	return (0);
}
