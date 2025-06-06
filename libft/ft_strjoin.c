/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:37:33 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/06 17:45:06 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*result;
// 	int		index;
// 	int		j;

// 	index = 0;
// 	j = 0;
// 	if (!s1 || !s2)
// 		return (NULL);
// 	result = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
// 	if (!result)
// 		return (NULL);
// 	while (s1[index])
// 	{
// 		result[index] = s1[index];
// 		index++;
// 	}
// 	while (s2[j])
// 	{
// 		result[index] = s2[j];
// 		index++;
// 		j++;
// 	}
// 	result[index] = '\0';
// 	if (s1)
// 		free((char *)s1); // added
// 	return (result);
// }

char *ft_strjoin(char const *s1, char const *s2)
{
    char *result;
    int index;
    int j;

    index = 0;
    j = 0;
    if (!s1 || !s2)
        return (NULL);
    result = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    if (!result)
        return (NULL);
    while (s1[index])
    {
        result[index] = s1[index];
        index++;
    }
    while (s2[j])
    {
        result[index] = s2[j];
        index++;
        j++;
    }
    result[index] = '\0';
    return (result);
}

/*int main(void)
{
	char *strs = "MMMMMMMMM";
	char *sep = "111  ";
	char *res;

	res = ft_strjoin(strs,sep);
	printf("%s", res);
}*/
