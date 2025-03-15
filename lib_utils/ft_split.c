/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:58:06 by etamazya          #+#    #+#             */
/*   Updated: 2024/02/26 20:17:37 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	count_tokens(char const *str, char delimeter)
{
	size_t	tokens;
	int		inside_token;

	tokens = 0;
	while (*str)
	{
		inside_token = 0;
		while (*str && *str == delimeter)
			++str;
		while (*str && *str != delimeter)
		{
			if (!inside_token)
			{
				tokens++;
				inside_token = 1;
			}
			++str;
		}
	}
	return (tokens);
}

char	**ft_split(char const *s, char c)
{
	const char	*new_s;
	char		**arr;
	int			words_amount;
	int			i;

	if (!s)
		return (NULL);
	words_amount = count_tokens(s, c);
	arr = (char **)malloc((words_amount + 1) * (sizeof(char *)));
	if (!arr)
		return (NULL);
	i = -1;
	while (++i < words_amount)
	{
		while (*s == c)
			s++;
		new_s = s;
		while (*s && *s != c)
			s++;
		arr[i] = ft_substr(new_s, 0, s - new_s);
		if (!arr[i] && ft_split(*arr, i))
			return (NULL);
	}
	arr[i] = NULL;
	return (arr);
}
/*
int main (void)
{
	char const *s = "___Hello_World__!!_";

	printf("%s", ft_split(s, '_'));
	return (0);
}
*/
