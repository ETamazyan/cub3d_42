/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 22:26:14 by etamazya          #+#    #+#             */
/*   Updated: 2024/02/11 15:58:30 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	check(char const *arr, char c)
{
	while (*arr)
	{
		if (*arr == c)
			return (1);
		arr++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	int		i;
	int		start;
	int		end;

	if (!s1 || !set)
		return (0);
	start = 0;
	while (s1[start] && check(set, s1[start]))
		start++;
	end = ft_strlen(s1) - 1;
	while (check(set, s1[end]) && start <= end)
		end--;
	trimmed = (char *)malloc(end - start + 2);
	if (!trimmed)
		return (NULL);
	i = 0;
	while (start + i <= end)
	{
		trimmed[i] = s1[start + i];
		i++;
	}
	trimmed[i] = '\0';
	return (trimmed);
}
/*
#include <stdio.h>

int main(void)
{
//	char *s1 = "   \t  \n\n \t\t  \\n \n \t\t\n  ";
//	char *s2 = "Hello \t  Please\n Trim me !";
	char *s1 = "  \t \t \n   \n\n\n\t";
	//char *s2 = "";
	char *ret = ft_strtrim(s1, " \n\t");
	printf("%s", ret);
	return (0);
}
int main(void)
{
	char *s1 = "\t \n He\nae\n!\n\t ";
	char *s2 = "Hello \t  Please\n Trim me !";
	char *res = ft_strtrim(s1, " \n\t");
	printf("%s\n", res);
}*/
