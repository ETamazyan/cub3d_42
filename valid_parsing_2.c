/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_parsing_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:45:22 by etamazya          #+#    #+#             */
/*   Updated: 2025/04/26 21:33:26 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// obrabotivat this one
// need
// 1
int	ft_check2(char const *set, char const str)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == str)
			return (1);
		i++;
	}
	return (0);
}
// 2
size_t	ft_startlen(const char *s1, const char *set)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && ft_check2(set, s1[i]))
		i++;
	while (s1[i] != '\n' && i > 0)
		i--;
	return (i);
}
// 3
int	ft_size(int start, int end)
{
	int	size;

	size = 0;
	size = end - start;
	return (size);
}
// 4
char	*ft_strtrim2(char *s1, char *set)
{
	char	*res;
	int		i;
	int		start;
	int		end;

	if (!s1 || !set)
		return (NULL);
	start = ft_startlen(s1, set);
	end = ft_strlen((char *)s1);
	while (end > start && ft_check2(set, s1[end - 1]))
		end--;
	res = (char *)malloc(sizeof(char) * (ft_size(start, end) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < ft_size(start, end))
	{
		res[i] = s1[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
