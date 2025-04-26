/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:09:51 by etamazya          #+#    #+#             */
/*   Updated: 2025/04/26 20:11:38 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_str_array(char **arr)
{
	int	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
void	free_res(char *buf, char *res)
{
	free(buf);
	free(res);
}