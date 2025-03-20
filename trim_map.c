#include "cub3D.h"

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

void	free_res(char *buf, char *res)
{
	free(buf);
	free(res);
}

void	only_whitespace(char	*res)
{
	int	i;

	i = 0;
	while (res[i])
	{
		if (!check_sep(res[i], "\n\t\v\f\r "))
			return ;
		i++;
	}
	free(res);
	printf("Error\nOnly whitespaces in map");
	exit(1);
}