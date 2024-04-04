/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:40:26 by emichels          #+#    #+#             */
/*   Updated: 2024/04/04 15:32:20 by emichels         ###   ########.fr       */
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
	t_map   newmap;
	
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			error_msg("Error\nFile open error\n", NULL, NULL);
		map_str = read_map(fd);
		//printf("%s\n", map_str);
		newmap = set_map_limits(map_str);
		is_valid_character(map_str);
		is_rectangle(newmap, map_str);
		//mlx_set_setting(MLX_MAXIMIZED, true);
		mlx_t	*mlx = mlx_init(WIDTH, HEIGHT, "title", true);
		if (!mlx)
			error_msg((char *)mlx_strerror(mlx_errno), NULL, NULL);
		mlx_image_t	*img = mlx_new_image(mlx, WIDTH, HEIGHT);
		if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
			error_msg((char *)mlx_strerror(mlx_errno), NULL, NULL);
		mlx_loop_hook(mlx, ft_hook, mlx);
		mlx_loop(mlx);
		mlx_terminate(mlx);
		// printf("max x: %i\n", newmap.max_x);
		// printf("max y: %i\n", newmap.max_y);
		// printf("collectibles: %i\n", newmap.collect_n);
		//free(map_str); // this might not be necessary, keeping it here just for leak checking
	}
	return (0);
}
