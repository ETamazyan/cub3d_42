/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:16:08 by etamazya          #+#    #+#             */
/*   Updated: 2024/02/04 14:06:52 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if ((count != 0 && size > 65536) || (size != 0 && count > 65536))
		return (NULL);
	str = malloc(count * size);
	if (!str)
		return (NULL);
	str = ft_memset(str, '\0', count * size);
	return (str);
}
