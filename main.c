/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:40:26 by emichels          #+#    #+#             */
/*   Updated: 2024/03/22 14:34:04 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(int argc, char **argv)
{
    int     fd;
    char    *map_str;
    t_map   newmap;
    
    if (argc == 2)
    {
        fd = open(argv[1], O_RDONLY);
        if (fd == -1)
            error_msg("Error\nFile open error\n", EXIT_FAILURE, NULL, NULL);
        map_str = read_map(fd);
        printf("%s\n", map_str);
        newmap = set_map_limits(map_str);
        is_valid_character(map_str);
        is_rectangle(newmap, map_str);
        printf("max x: %i\n", newmap.max_x);
        printf("max y: %i\n", newmap.max_y);
        printf("collectibles: %i\n", newmap.collect_n);
        free(map_str); // this might not be necessary, keeping it here just for leak checking
    }
    return (0);
}
