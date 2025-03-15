/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:45:22 by etamazya          #+#    #+#             */
/*   Updated: 2025/03/15 12:53:39 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**fd_parse(int fd)
{
	char	*each_line;
	char	*temp;
	char	**res;

	each_line = get_next_line(fd);
	temp = each_line;
	if (!each_line)
		return (NULL);
	while (temp)
	{
		temp = get_next_line(fd);
		each_line = ft_strjoin(each_line, temp);
		free(temp);
	}
	// just from so_long___START:
	// each_line = check_newline2(each_line);
	// check_newline(each_line);
	// res = ft_split(each_line, '\n');
	// check_whitespaces(res);
	// free (each_line);
	// return (res);
	// just from so_long___END:
	(void)res;
	return (NULL);
}

// **********

char	*check_newline2(char *join)
{
	char	*temp;

	temp = join;
	join = ft_strtrim2(join, " \t\n\v\f\r");
	free(temp);
	return (join);
}
int	ft_check2(char const *set, char const str)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == str)
			return (1);
		i++;
	}
	return (0);
}
// *****************
// *****************

void	check_newline(char *join)
{
	int	i;

	i = 0;
	while (join[i])
	{
		if (join[i] == '\n' && join[i + 1] == '\n')
		{
			write(2, "Invalid map\n", 12);
			exit(0);
		}
		i++;
	}
}
void	check_whitespaces(char **res)
{
	char	*temp;
	int		i;

	temp = NULL;
	i = 0;
	while (res[i])
	{
		temp = res[i];
		res[i] = ft_strtrim(res[i], " \t\n\v\f\r");
		free(temp);
		i++;
	}
}
size_t	ft_check(char const *set, char const str)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == str)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	i;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1);
	while (ft_check(set, s1[end - 1]))
		end--;
	res = (char *)malloc(sizeof(char) * (end + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < end)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}


//******************** */
//******************** */
//******************** */

size_t	ft_startlen(const char *s1, const char *set)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && ft_check2(set, s1[i]))
		i++;
	while (s1[i] != '\n' && i > 0)
		i--;
	return (i);
}

int	ft_size(int start, int end)
{
	int	size;

	size = 0;
	size = end - start;
	return (size);
}

char	*ft_strtrim2(char *s1, char *set)
{
	char	*res;
	int		i;
	int		start;
	int		end;

	if (!s1 || !set)
		return (NULL);
	start = ft_startlen(s1, set);
	end = ft_strlen((char *)s1);
	while (end > start && ft_check2(set, s1[end - 1]))
		end--;
	res = (char *)malloc(sizeof(char) * (ft_size(start, end) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < ft_size(start, end))
	{
		res[i] = s1[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}