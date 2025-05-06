/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:09:51 by etamazya          #+#    #+#             */
/*   Updated: 2025/05/06 19:28:52 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//9-rd
// void	free_str_array(char **arr)
// {
// 	int	i = 0;
// 	while (arr[i])
// 		free(arr[i++]);
// 	free(arr);
// }
//7
// void	free_res(char *buf, char *res)
// {
// 	if (buf != NULL && buf != res)
// 		free(buf);
// 	if (res)
// 	{
// 		free(res);
// 		res = NULL;
// 	}
// }


void clean_dbl_chr_ptr(char **ptr) {
    if (!ptr) return;

    int i = 0;
    while (ptr[i] != NULL) {
        free(ptr[i]);
        i++;
    }
    free(ptr);
}
