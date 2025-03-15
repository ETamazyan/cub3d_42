/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:07:46 by etamazya          #+#    #+#             */
/*   Updated: 2024/02/04 17:03:14 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*s1_dup;

	i = 0;
	s1_dup = (char *)malloc(ft_strlen(s1) + 1);
	if (!s1_dup)
		return (NULL);
	while (s1[i] != '\0')
	{
		s1_dup[i] = s1[i];
		i++;
	}
	s1_dup[i] = '\0';
	return ((char *)s1_dup);
}
/*
#include <stdio.h>
int main(void)
{
	printf("%s", ft_strdup("hello"));
}
*/
