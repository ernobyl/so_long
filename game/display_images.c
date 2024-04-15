/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_images.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:16:17 by emichels          #+#    #+#             */
/*   Updated: 2024/04/15 15:56:35 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	display_map(t_map *map)
{
		int	i;
		
		load_textures(map);
		if (!map->images)
			struct_error((char *)mlx_strerror(mlx_errno), map);
		resize_images(map);
		i = 0;
		map->y = 0;
		map->x = 0;
		while (map->str[i])
		{
			if (map->str[i] == '1')
			{
				if (mlx_image_to_window(map->mlx, map->images->w_img, map->x * WIDTH, map->y * HEIGHT) < 0)
					struct_error((char *)mlx_strerror(mlx_errno), map);
				if (map->x == map->max_x)
				{
					map->y++;
					map->x = 0;
				}
				else
					map->x++;
			}
			else if (map->str[i] == '0' || map->str[i] == 'P' || map->str[i] == 'C')
			{
				if (mlx_image_to_window(map->mlx, map->images->f_img, map->x * WIDTH, map->y * HEIGHT) < 0)
					struct_error((char *)mlx_strerror(mlx_errno), map);
				if (map->str[i] == 'C')
				{
					if (mlx_image_to_window(map->mlx, map->images->c_img, map->x * WIDTH, map->y * HEIGHT) < 0)
						struct_error((char *)mlx_strerror(mlx_errno), map);
				}
				map->x++;
			}
			else if (map->str[i] == 'E')
			{
				if (mlx_image_to_window(map->mlx, map->images->dc_img, map->x * WIDTH, map->y * HEIGHT) < 0)
					struct_error((char *)mlx_strerror(mlx_errno), map);
				if (mlx_image_to_window(map->mlx, map->images->do_img, map->x * WIDTH, map->y * HEIGHT) < 0)
					struct_error((char *)mlx_strerror(mlx_errno), map);
				map->images->do_img->enabled = false;
				map->x++;
			}
			i++;
		}
}

void	display_player(t_map *map)
{
	map->y = 1;
	while (map->y < map->max_y)
	{
		map->x = 1;
		while (map->arr[map->y][map->x])
		{
			if (map->arr[map->y][map->x] == 'P')
			{
				map->plr_y = map->y;
				map->plr_x = map->x;
				if (mlx_image_to_window(map->mlx, map->images->p_img, map->x * WIDTH, map->y * HEIGHT) < 0)
					struct_error((char *)mlx_strerror(mlx_errno), map);
				break;
			}
			map->x++;
		}
		if (map->arr[map->y][map->x] == 'P')
			break;
		map->y++;
	}
}