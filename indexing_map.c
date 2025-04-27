/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexing_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:24:57 by maavalya          #+#    #+#             */
/*   Updated: 2025/04/27 22:36:22 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* initializing map elements, petqa ciklov */
// void    separate_elements(char **map, t_data *map_dim)
// {
//     int i;

//     i = 0;
//     while (map[i])
//     {
//         if (!ft_strncmp(map[i], "SO", 2))
//             map_dim->south = ft_strdup(map[i]);
//         else if (!ft_strncmp(map[i], "EA", 2))
//             map_dim->east = ft_strdup(map[i]);
//         else if (!ft_strncmp(map[i], "WE", 2))
//             map_dim->west = ft_strdup(map[i]);
//         else if (!ft_strncmp(map[i], "NO", 2))
//             map_dim->north = ft_strdup(map[i]);
//         else if (!ft_strncmp(map[i], "F", 1))
//             map_dim->F_color = ft_strdup(map[i]);
//         else if (!ft_strncmp(map[i], "C", 1))
//             map_dim->C_color = ft_strdup(map[i]);
//         else
//             {
//                 map_dim->map = ft_strdup_2d(map, i);
//                 break;
//             }
//         i++;
//     }
// }