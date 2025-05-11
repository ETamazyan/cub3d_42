/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 13:32:06 by etamazya          #+#    #+#             */
/*   Updated: 2025/05/11 19:57:53 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	copy_map(t_data *dbase, char **lines, int i, int j)
{
	int	k;
	int	count;

	while (lines[i])
		i++;
	count = i;
	dbase->map = (char **)malloc(sizeof(char *) * (count + 1));
	if (!dbase->map)
		print_err_exit(dbase, "Error\nWhile alocating\n");
	i = 0;
	while (lines[i])
	{
		dbase->map[j] = ft_strdup(lines[i]);
		if (!dbase->map[j])
		{
			k = 0;
			while (k < j)
				free(dbase->map[k]);
			print_err_exit(dbase, "Error\nWhile allocating\n");
		}
		j++;
		i++;
	}
	dbase->map[count] = NULL;
}

int	keep_valid_map(char **lines, t_data *dbase) // ete 0 error
{
	if (!lines || !*lines)
		return (0);
	if (!check_chars(lines) || !check_walls(lines) || !check_player(lines) \
|| !check_disordered_wall(lines, 1, 1) || !check_door(lines))
		return (1);
	copy_map(dbase, lines, 0, 0);
	return (0);
}
