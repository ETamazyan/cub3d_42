/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <el.tamazyan03@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:42:22 by etamazya          #+#    #+#             */
/*   Updated: 2025/03/04 21:39:06 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void is_fd_valid(t_data *data, char *path)
{
	while (*path != '.')
		path++;
	if (ft_strncmp(".cub", path, 4) != 0)
		print_error(data, "Error: Invalid file\n");
    //if not exit() but with printing correspond error message.
}