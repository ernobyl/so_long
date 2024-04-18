/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:23:58 by emichels          #+#    #+#             */
/*   Updated: 2024/04/17 14:14:06 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	free_textures(t_texture *textures)
{
	mlx_delete_texture(textures->wall);
	mlx_delete_texture(textures->floor);
	mlx_delete_texture(textures->player);
	mlx_delete_texture(textures->collect);
	mlx_delete_texture(textures->door_clo);
	mlx_delete_texture(textures->door_opn);
}

void	free_images(t_map *map)
{
	if (map->images->w_img)
		mlx_delete_image(map->mlx, map->images->w_img);
	if (map->images->f_img)
		mlx_delete_image(map->mlx, map->images->f_img);
	if (map->images->p_img)
		mlx_delete_image(map->mlx, map->images->p_img);
	if (map->images->c_img)
		mlx_delete_image(map->mlx, map->images->c_img);
	if (map->images->dc_img)
		mlx_delete_image(map->mlx, map->images->dc_img);
	if (map->images->do_img)
		mlx_delete_image(map->mlx, map->images->do_img);
	free(map->images);
}

void	struct_error(char *msg, t_map *map)
{
	if (map->str)
		free(map->str);
	if (map->arr)
		ft_free(map->arr);
	if (map->images)
		free_images(map);
	if (map->mlx)
		mlx_terminate(map->mlx);
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

void	texture_error(char *msg, t_map *map, t_texture *textures)
{
	if (map->arr)
		ft_free(map->arr);
	if (textures->wall)
		mlx_delete_texture(textures->wall);
	if (textures->floor)
		mlx_delete_texture(textures->floor);
	if (textures->player)
		mlx_delete_texture(textures->player);
	if (textures->collect)
		mlx_delete_texture(textures->collect);
	if (textures->door_clo)
		mlx_delete_texture(textures->door_clo);
	if (textures->door_opn)
		mlx_delete_texture(textures->door_opn);
	free(textures);
	if (map->images)
		free_images(map);
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

void	simple_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}
