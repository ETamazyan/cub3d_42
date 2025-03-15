/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:25:09 by etamazya          #+#    #+#             */
/*   Updated: 2024/02/26 20:22:49 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*str1;

	str1 = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		str1[i] = c;
		i++;
	}
	return (str1);
}
/*
#include <string.h>

int main()
{
	char *str = "abcde";
   	printf("%s", memset(str, '4', 10)); 
	return 0;
}
*/
