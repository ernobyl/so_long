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
	map->arr = NULL;
	map->images = NULL;
}

void	count_steps(t_map *map)
{
	map->steps++;
	ft_putstr_fd("step count: ", 1);
	ft_putnbr_fd(map->steps, 1);
	ft_putchar_fd('\n', 1);
}

void	move_right(t_map *map)
{
	if (map->arr[map->plr_y][map->plr_x + 1] == '1')
		return;
	map->plr_x++;
	map->images->p_img->instances->x += WIDTH;
	count_steps(map);
	//count_collectibles(map);
}

void	move_left(t_map *map)
{
	if (map->arr[map->plr_y][map->plr_x - 1] == '1')
		return;
	map->plr_x--;
	map->images->p_img->instances->x -= WIDTH;
	count_steps(map);
	//count_collectibles(map);
}

void	move_down(t_map *map)
{
	if (map->arr[map->plr_y + 1][map->plr_x] == '1')
		return;
	map->plr_y++;
	map->images->p_img->instances->y += HEIGHT;
	count_steps(map);
	//count_collectibles(map);
}

void	move_up(t_map *map)
{
	if (map->arr[map->plr_y - 1][map->plr_x] == '1')
		return;
	map->plr_y--;
	map->images->p_img->instances->y -= HEIGHT;
	count_steps(map);
	//count_collectibles(map);
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(map->mlx);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move_right(map);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move_left(map);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move_down(map);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		move_up(map);
}

void	resize_images(t_map *map)
{
	mlx_resize_image(map->images->w_img, WIDTH, HEIGHT);
	mlx_resize_image(map->images->f_img, WIDTH, HEIGHT);
	mlx_resize_image(map->images->p_img, WIDTH, HEIGHT);
	mlx_resize_image(map->images->c_img, WIDTH, HEIGHT);
	mlx_resize_image(map->images->dc_img, WIDTH, HEIGHT);
	//mlx_resize_image(map->images->do_img, WIDTH, HEIGHT);
}

void	load_textures(t_map *map)
{
	t_texture	*textures;

	textures = ft_calloc(1, sizeof(t_texture));
	map->images = ft_calloc(1, sizeof(t_image));
	textures->wall = mlx_load_png("./textures/wall.png");
	textures->floor = mlx_load_png("./textures/floor.png");
	textures->player = mlx_load_png("./textures/player.png");
	textures->collect = mlx_load_png("./textures/collect.png");
	textures->door_clo = mlx_load_png("./textures/door_closed.png");
	//textures->door_opn = mlx_load_png("./textures/door_open.png");
	map->images->w_img = mlx_texture_to_image(map->mlx, textures->wall);
	map->images->f_img = mlx_texture_to_image(map->mlx, textures->floor);
	map->images->p_img = mlx_texture_to_image(map->mlx, textures->player);
	map->images->c_img = mlx_texture_to_image(map->mlx, textures->collect);
	map->images->dc_img = mlx_texture_to_image(map->mlx, textures->door_clo);
	//map->images->do_img = mlx_texture_to_image(map->mlx, textures->door_opn);
	free(textures);
}

int32_t	main(int argc, char **argv)
{
	int     fd;
	char    *map_str;
	t_map   map;
	
	if (argc == 2)
	{
		init_map_struct(&map);
		valid_extension(argv[1]);
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			error_msg("Error\nFile open error\n", NULL, NULL);
		map_str = read_map(fd);
		// printf("%s\n", map_str);
		map = set_map_limits(map_str);
		is_valid_character(map_str);
		is_rectangle(map, map_str);
		map.arr = ft_split(map_str, '\n');
		mlx_set_setting(MLX_MAXIMIZED, true);
		map.mlx = mlx_init((map.max_x + 1) * WIDTH, (map.max_y + 1) * HEIGHT, "title", false);
		if (!map.mlx)
			error_msg((char *)mlx_strerror(mlx_errno), NULL, NULL);
// TEXTURES
		int			i;
		
		load_textures(&map);
		if (!map.images)
			error_msg((char *)mlx_strerror(mlx_errno), map_str, NULL);
		resize_images(&map);
		i = 0;
		map.y = 0;
		map.x = 0;
		while (map_str[i])
		{
			if (map_str[i] == '1')
			{
				if (mlx_image_to_window(map.mlx, map.images->w_img, map.x * WIDTH, map.y * HEIGHT) < 0)
					error_msg((char *)mlx_strerror(mlx_errno), map_str, NULL);
				if (map.x == map.max_x)
				{
					map.y++;
					map.x = 0;
				}
				else
					map.x++;
			}
			else if (map_str[i] == '0' || map_str[i] == 'P')
			{
				if (mlx_image_to_window(map.mlx, map.images->f_img, map.x * WIDTH, map.y * HEIGHT) < 0)
					error_msg((char *)mlx_strerror(mlx_errno), map_str, NULL);
				map.x++;
			}
			else if (map_str[i] == 'C')
			{
				if (mlx_image_to_window(map.mlx, map.images->c_img, map.x * WIDTH, map.y * HEIGHT) < 0)
					error_msg((char *)mlx_strerror(mlx_errno), map_str, NULL);
				map.x++;
			}
			else if (map_str[i] == 'E')
			{
				if (mlx_image_to_window(map.mlx, map.images->dc_img, map.x * WIDTH, map.y * HEIGHT) < 0)
					error_msg((char *)mlx_strerror(mlx_errno), map_str, NULL);
				map.x++;
			}
			i++;
		}
// TEXTURES
//	PLAYER START POSITION
		map.y = 1;
		while (map.y < map.max_y)
		{
			map.x = 1;
			while (map.arr[map.y][map.x])
			{
				if (map.arr[map.y][map.x] == 'P')
				{
					map.plr_y = map.y;
					map.plr_x = map.x;
					if (mlx_image_to_window(map.mlx, map.images->p_img, map.x * WIDTH, map.y * HEIGHT) < 0)
						error_msg((char *)mlx_strerror(mlx_errno), map_str, NULL);
					break;
				}
				map.x++;
			}
			if (map.arr[map.y][map.x] == 'P')
				break;
			map.y++;
		}
//	PLAYER START POSITION
		mlx_key_hook(map.mlx, &my_keyhook, &map);
		mlx_loop(map.mlx);
		mlx_terminate(map.mlx);
		printf("max x: %i\n", map.max_x);
		printf("max y: %i\n", map.max_y);
		printf("player x pos: %i\n", map.plr_x);
		printf("player y pos: %i\n", map.plr_y);
		printf("collectibles: %i\n", map.collect_n);
		//free(map_str); // this might not be necessary, keeping it here just for leak checking
	}
	return (0);
}
