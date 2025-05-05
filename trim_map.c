/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 06:13:34 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/05 21:08:12 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// 1
static int	check_sep(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}
// 2 // 6-rd
char	*cut_front(char *old)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	while(old[i] && check_sep(old[i], "\n\t\v\f\r "))
		i++;
	new = (char *)malloc(ft_strlen(old + i) * sizeof(char) + 1);
	j = 0;
	while(old[i + j])
	{
		new[j] = old[i + j];
		j++;
	}
	free(old);
	new[j] = '\0';
	return (new);
}

// 3 //4-rd
void	only_whitespace(t_data *dbase, char *res)
{
	int	i;

	i = 0;
	while (res[i])
	{
		if (!check_sep(res[i], "\n\t\v\f\r "))
			return ;
		i++;
	}
	free(res);
	print_err_exit(dbase, "Error\nOnly whitespaces in map");
}