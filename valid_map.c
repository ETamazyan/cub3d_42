/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 13:32:06 by etamazya          #+#    #+#             */
/*   Updated: 2025/05/07 13:52:26 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	copy_map(t_data *dbase, char **lines, int i, int j)
{
	int	count;

	i = 0;
	while (lines[i])
		i++;
	count = i;
	dbase->map = (char **)malloc(sizeof(char *) * (count + 1));
	if (!dbase->map)
	{
		// clean_dbl_chr_ptr(lines);
		print_err_exit(dbase, "Error\nWhile alocating\n");
	}
	i = 0;
	while (lines[i])
	{
		dbase->map[j] = ft_strdup(lines[i]);
		if (!dbase->map[j])
		{
			for (int k = 0; k < j; k++)
				free(dbase->map[k]);
			// clean_dbl_chr_ptr(lines);
			print_err_exit(dbase, "Error\nWhile allocating\n");
		}
		j++;
		i++;
	}
	dbase->map[count] = NULL;
	// clean_dbl_chr_ptr(lines);
}

// ete sxal exit// kap chuni inch e veradardznum// datarkel d_base-y
int keep_valid_map(char **lines, t_data *dbase) // ete 0 error
{
	while(*lines)
	if (!check_chars(lines) || !check_walls(lines) || !check_player(lines)\
	|| !check_disordered_wall(lines, 1, 1) || !check_door(lines))
	{
		// clean_dbl_chr_ptr(lines);
		print_err_exit(dbase, "");
	}
	copy_map(dbase, lines, 0, 0); // free line
	return (1);
}