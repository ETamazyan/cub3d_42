/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 06:13:34 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/07 18:29:58 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*cut_front(char *old)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	while (old[i] && check_sep(old[i], "\n\t\v\f\r "))
		i++;
	new = (char *)malloc(ft_strlen(old + i) * sizeof(char) + 1);
	j = 0;
	while (old[i + j])
	{
		new[j] = old[i + j];
		j++;
	}
	if (old)
		free(old);
	new[j] = '\0';
	return (new);
}
