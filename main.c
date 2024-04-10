/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:40:26 by emichels          #+#    #+#             */
/*   Updated: 2024/04/10 16:31:33 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// void	movement(mlx_t *mlx, t_image *images, t_map map)
// {
// 	if (mlx_is_key_down(mlx, MLX_KEY_W)
// 		&& map.map_arr[map.plr_y - 1][map.plr_x] != '1')
// 		images->p_img->instances[0].y -= HEIGHT;
// 	mlx_key_hook()
// }

void	ft_hook(void *param)
{
	mlx_t	*mlx = param;
	
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void	resize_images(t_image *images)
{
	mlx_resize_image(images->w_img, WIDTH, HEIGHT);
	mlx_resize_image(images->f_img, WIDTH, HEIGHT);
	mlx_resize_image(images->p_img, WIDTH, HEIGHT);
	mlx_resize_image(images->c_img, WIDTH, HEIGHT);
	mlx_resize_image(images->dc_img, WIDTH, HEIGHT);
	//mlx_resize_image(images->do_img, WIDTH, HEIGHT);
}

t_image	*load_textures(mlx_t *mlx)
{
	t_texture	*textures;
	t_image		*images;

	textures = ft_calloc(1, sizeof(t_texture));
	images = ft_calloc(1, sizeof(t_image));
	textures->wall = mlx_load_png("./textures/wall.png");
	textures->floor = mlx_load_png("./textures/floor.png");
	textures->player = mlx_load_png("./textures/player.png");
	textures->collect = mlx_load_png("./textures/collect.png");
	textures->door_clo = mlx_load_png("./textures/door_closed.png");
	//textures->door_opn = mlx_load_png("./textures/door_open.png");
	images->w_img = mlx_texture_to_image(mlx, textures->wall);
	images->f_img = mlx_texture_to_image(mlx, textures->floor);
	images->p_img = mlx_texture_to_image(mlx, textures->player);
	images->c_img = mlx_texture_to_image(mlx, textures->collect);
	images->dc_img = mlx_texture_to_image(mlx, textures->door_clo);
	//images->do_img = mlx_texture_to_image(mlx, textures->door_opn);
	return (images);
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
		map.map_arr = ft_split(map_str, '\n');
//	PLAYER START POSITION
		map.y = 1;
		while (map.y < map.max_y)
		{
			map.x = 1;
			while (map.map_arr[map.y][map.x])
			{
				if (map.map_arr[map.y][map.x] == 'P')
				{
					map.plr_y = map.y;
					map.plr_x = map.x;
					break;
				}
				map.x++;
			}
			if (map.map_arr[map.y][map.x] == 'P')
				break;
			map.y++;
		}
//	PLAYER START POSITION
		mlx_set_setting(MLX_MAXIMIZED, true);
		mlx_t	*mlx;
		mlx = mlx_init((map.max_x + 1) * WIDTH, (map.max_y + 1) * HEIGHT, "title", false);
		if (!mlx)
			error_msg((char *)mlx_strerror(mlx_errno), NULL, NULL);
// TEXTURES
		int			i;
		t_image		*images;
		
		images = load_textures(mlx);
		if (!images)
			error_msg((char *)mlx_strerror(mlx_errno), map_str, NULL);
		resize_images(images);
		i = 0;
		map.y = 0;
		map.x = 0;
		while (map_str[i])
		{
			if (map_str[i] == '1')
			{
				if (mlx_image_to_window(mlx, images->w_img, map.x * WIDTH, map.y * HEIGHT) < 0)
					error_msg((char *)mlx_strerror(mlx_errno), map_str, NULL);
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
				if (mlx_image_to_window(mlx, images->f_img, map.x * WIDTH, map.y * HEIGHT) < 0)
					error_msg((char *)mlx_strerror(mlx_errno), map_str, NULL);
				map.x++;
			}
			else if (map_str[i] == 'P')
			{
				if (mlx_image_to_window(mlx, images->p_img, map.x * WIDTH, map.y * HEIGHT) < 0)
					error_msg((char *)mlx_strerror(mlx_errno), map_str, NULL);
				map.x++;
			}
			else if (map_str[i] == 'C')
			{
				if (mlx_image_to_window(mlx, images->c_img, map.x * WIDTH, map.y * HEIGHT) < 0)
					error_msg((char *)mlx_strerror(mlx_errno), map_str, NULL);
				map.x++;
			}
			else if (map_str[i] == 'E')
			{
				if (mlx_image_to_window(mlx, images->dc_img, map.x * WIDTH, map.y * HEIGHT) < 0)
					error_msg((char *)mlx_strerror(mlx_errno), map_str, NULL);
				map.x++;
			}
			i++;
		}
// TEXTURES
		mlx_loop_hook(mlx, ft_hook, mlx);
		mlx_loop(mlx);
		mlx_terminate(mlx);
		printf("max x: %i\n", map.max_x);
		printf("max y: %i\n", map.max_y);
		printf("player x pos: %i\n", map.plr_x);
		printf("player y pos: %i\n", map.plr_y);
		printf("collectibles: %i\n", map.collect_n);
		//free(map_str); // this might not be necessary, keeping it here just for leak checking
	}
	return (0);
}
