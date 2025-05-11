/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:47:02 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/11 19:20:16 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_string_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static int	ft_strlen_sep(char *str, char c)
{
	int	len;

	len = 0;
	while (*str != '\0' && *str != c)
	{
		len++;
		str++;
	}
	return (len);
}

static char	*ft_word(char *str, char c)
{
	int		len_word;
	int		i;
	char	*word;

	i = 0;
	len_word = ft_strlen_sep(str, c);
	word = (char *)malloc(sizeof(char) * len_word + 1);
	if (!word)
		return (NULL);
	while (i < len_word)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		flag;
	int		i;

	i = 0;
	flag = 1;
	res = check_s_mlc_res(s, c);
	while (*s != '\0' && res)
	{
		if (*s != '\0' && *s == c)
			flag = 1;
		if (*s != '\0' && flag == 1 && *s != c)
		{
			res[i] = ft_word((char *)s, c);
			if (!res[i])
				return (free_string_array(res), NULL);
			flag = 0;
			i++;
		}
		s++;
	}
	res[i] = 0;
	return (res);
}

/*#include <stdio.h>
int main(void)
{
 char **split;
 split = ft_split("aaa\taa aa\taaa", ' ');
 for(int i = 0; split[i] != 0; i++)
 {
	 printf("%s\n", split[i]);
 }
}*/
