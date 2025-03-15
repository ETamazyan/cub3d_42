/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:25:22 by etamazya          #+#    #+#             */
/*   Updated: 2024/01/20 18:46:55 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;

	i = ft_strlen(s);
	while (i > 0 && s[i] != (char)c)
		i--;
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	else
		return (NULL);
}
