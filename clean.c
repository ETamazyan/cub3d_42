/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:09:51 by etamazya          #+#    #+#             */
/*   Updated: 2025/05/07 18:19:12 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_string_array(char **array)
{
	int	i;
    if (array == NULL) {
        return;
    }
	i = 0;
    while (array[i] != NULL)
	{
        free(array[i]);
		i++;
	}

    free(array);
}

void clean_dbl_chr_ptr(char **ptr) {
    if (!ptr) return;

    int i = 0;
    while (ptr[i] != NULL) {
        free(ptr[i]);
        i++;
    }
    free(ptr);
}
