/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:59:52 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/11 18:32:22 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_sep(char c, char *charset)
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

static int	loop(char const *s1, char const *set, int i)
{
	while (s1[i])
	{
		if (check_sep((char)s1[i], (char *)set) == 1)
			i++;
		else
			break ;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*res;
	size_t	len;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	i = loop(s1, set, i);
	len = ft_strlen(((char *)s1 + i));
	while (len != 0)
	{
		if (check_sep((s1 + i)[len - 1], (char *)set) == 1)
			len--;
		else
			break ;
	}
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, (char *)(s1 + i), len + 1);
	res[len] = '\0';
	free((char *)s1);
	return (res);
}

/*#include <stdio.h>
int main(void)
{
	char *ch = "ajsjmhdjhmd****kjdnkid++ewudr-";
	char *set = "++*-";
	printf("%s, ", ft_strtrim(ch, set));
}*/
