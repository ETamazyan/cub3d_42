/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:17:31 by elen_t13          #+#    #+#             */
/*   Updated: 2025/05/11 19:19:33 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_strings(char *str, char c)
{
	int	count;
	int	flag;

	flag = 1;
	count = 0;
	while (*str != '\0')
	{
		if (*str == c && flag == 0)
			flag = 1;
		if (*str != '\0' && *str != c && flag == 1)
		{
			count++;
			flag = 0;
		}
		str++;
	}
	return (count);
}

char	**check_s_mlc_res(char const *s, char c)
{
	char	**res;

	if (!s)
		return (NULL);
	res = (char **)malloc((count_strings((char *)s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	return (res);
}
