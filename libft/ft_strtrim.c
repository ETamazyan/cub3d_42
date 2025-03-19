/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maavalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:59:52 by maavalya          #+#    #+#             */
/*   Updated: 2024/01/26 15:59:54 by maavalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	while (s1)
	{
		if (check_sep((char)*s1, (char *)set) == 1)
			s1++;
		else
			break ;
	}
	len = ft_strlen((char *)s1);
	while (len != 0)
	{
		if (check_sep(s1[len - 1], (char *)set) == 1)
			len--;
		else
			break ;
	}
	res = (char *)malloc(sizeof(char) * len + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, (char *)s1, len + 1);
	return (res);
}

/*#include <stdio.h>
int main(void)
{
	char *ch = "ajsjmhdjhmd****kjdnkid++ewudr-";
	char *set = "++*-";
	printf("%s, ", ft_strtrim(ch, set));
}*/
