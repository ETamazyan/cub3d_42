/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:03:10 by etamazya          #+#    #+#             */
/*   Updated: 2025/04/26 17:51:27 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int argc, char **argv)
{
	t_data	dbase;

	if (argc != 2)
		return (printf("Error: Invalid amount of arguments.\n"), 1);
	// print_error(data, "Error: Invalid amount of arguments.\n");
	// fd = open(argv[1], O_RDONLY);
	// if (fd < 0)
	// 	// print_error(data, "Error: Invalid cannot read file.\n");
	// 	printf("reading failed");
	//check validity then create data type
	if (valid_and_parsing(&dbase, argv[1]) == 1)
		return (1);
	return (0);
}
