/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:47:26 by etamazya          #+#    #+#             */
/*   Updated: 2024/01/31 16:43:56 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*for_s;

	i = 0;
	for_s = (unsigned char *)s;
	while (i < n)
	{
		if (for_s[i] == (unsigned char)c)
			return ((void *)for_s + i);
		i++;
	}
	return (NULL);
}
