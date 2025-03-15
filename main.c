/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:03:10 by etamazya          #+#    #+#             */
/*   Updated: 2025/03/13 15:10:59 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int argc, char **argv)
{
	int		fd;
	t_data	*data;

	fd = 0;
	data = NULL;
	(void)data;
	if (argc != 2)
		print_error(data, "Error: Invalid amount of arguments.\n");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		print_error(data, "Error: Invalid cannot read file.\n");
	is_fd_valid(data, argv[1]);
	data->map = fd_parse(fd);
	return (0);
}