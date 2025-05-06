/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:59:52 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/06 17:42:19 by etamazya         ###   ########.fr       */
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

// char	*ft_strtrim(char const *s1, char const *set)
// {
// 	int i = 0;
// 	char	*res;
// 	size_t	len;

// 	if (!s1 || !set)
// 		return (NULL);
// 	while (s1[i])
// 	{
// 		if (check_sep((char)s1[i], (char *)set) == 1)
// 			i++;
// 		else
// 			break ;
// 	}
// 	len = ft_strlen(((char *)s1 + i));
// 	while (len != 0)
// 	{
// 		if (check_sep((s1 + i)[len - 1], (char *)set) == 1)
// 			len--;
// 		else
// 			break ;
// 	}
// 	res = (char *)malloc(sizeof(char) * len + 1);
// 	if (!res)
// 		return (NULL);
// 	ft_strlcpy(res, (char *)s1, len + 1);
// 	s1 = NULL;
// 	return (res);
// }

char *ft_strtrim(char const *s1, char const *set)
{
    int i = 0;
    char *res;
    size_t len;

    if (!s1 || !set)
        return (NULL);
    while (s1[i])
    {
        if (check_sep((char)s1[i], (char *)set) == 1)
            i++;
        else
            break;
    }
    len = ft_strlen(((char *)s1 + i));
    while (len != 0)
    {
        if (check_sep((s1 + i)[len - 1], (char *)set) == 1)
            len--;
        else
            break;
    }
    res = (char *)malloc(sizeof(char) * (len + 1));
    if (!res)
        return (NULL);
    ft_strlcpy(res, (char *)(s1 + i), len + 1);
    res[len] = '\0';
    return (res);
}


/*#include <stdio.h>
int main(void)
{
	char *ch = "ajsjmhdjhmd****kjdnkid++ewudr-";
	char *set = "++*-";
	printf("%s, ", ft_strtrim(ch, set));
}*/
