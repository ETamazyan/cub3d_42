/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_parsing_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:04:33 by etamazya          #+#    #+#             */
/*   Updated: 2025/04/26 14:04:18 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//2
int is_line_valid(const char *line, int *count, int order)
{
	*count += 1;
	while (*line && order > 6)
	{
		if (*line != '1' && *line != ' ' && *line != '\t')
			return (0);
		line++;
	}
	return (1);
}
//3.1
int check_no_so_we_ea(const char *line, const  char *temp)
{
    if (ft_strncmp(line, "NO", 2) == 0)
	{
		if (ft_strncmp(temp, "./assets/no.xpm", 15) != 0)
			return(printf("Error: Path for NO texture is not correct. \
Expected: ./assets/no.xpm\n"), 1);
	}
	else if (ft_strncmp(line, "SO", 2) == 0)
	{
		if (ft_strncmp(temp, "./assets/so.xpm", 15) != 0)
			return(printf("Error: Path for SO texture is not correct. \
Expected: ./assets/so.xpm\n"), 1);
	}
    else if (ft_strncmp(line, "WE", 2) == 0)
	{
		if (ft_strncmp(temp, "./assets/we.xpm", 15) != 0)
			return(printf("Error: Path for WE texture is not correct. \
Expected: ./assets/we.xpm\n"), 1);
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		if (ft_strncmp(temp, "./assets/ea.xpm", 15) != 0)
			return(printf("Error: Path for EA texture is not correct. \
Expected: ./assets/ea.xpm\n"), 1);
	}
    return (0);
}

//3
// if 1 error
int is_valid_identifier(const char *line)
{
	const char *temp;
	
	if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0 || 
	ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
	{
        temp = line + 2;
        if (!(*temp >= 9 && *temp <= 12) && *temp != 32)
            return (printf("Error: Texture path should be seperated.\n"), 1);
        else
            temp = temp + 1;
        if (*temp == '\0')
            return (printf("Error: Empty path for texture.\n"), 1);
        if (check_no_so_we_ea(line, temp) == 1)
            return (1);
        while (*temp != '\0')
        {
            if (!ft_isalnum(*temp) && *temp != '/' && *temp != '.')
                return (printf("Error: Invalid character in path: %s\n", temp), 1);
            temp++;
        }
    } 
	else if (ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0)
	{
		temp = line + 1;
        if ((*temp >= 9 && *temp <= 12) || *temp == 32)
        return (printf("Error: Texture path should be deperated.\n"), 1);    
        int r, g, b;
		if (sscanf(temp, "%d,%d,%d", &r, &g, &b) != 3)
			return (printf("Error: Invalid RGB values\n"), 0);
		if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
			return (printf("Error: RGB values out of range\n"), 0);
		return (1);
	}
    else
    {
        // aysinqn voch mi no so we ea f c chka
        return (1);
    }
	return (0);
}
//1
// if 1 error
int validate_file(char **map, int counter, int i)
{
	int exp_o;
	int first_f_c;
	const char *line;
	
	exp_o = 0;
	first_f_c = 0;	
	while (map[i] != NULL) 
	{
		line = map[i];
		if (line[0] == '\n')
			continue;
		if (is_line_valid(line, &counter, (exp_o + first_f_c)))
		{
			printf("line = %s, num = %d", line, (exp_o + first_f_c));
			if (is_valid_identifier(line) == 1)
				return (1);		
			// if ((exp_o + first_f_c) < 6)
			// 	printf("Error: map cannot be before identifiers\n");
			return (1);
		}
		if (check_identifier_order(line, &exp_o, &first_f_c) == 1)
			return (printf("Error: Invalid order or unknown identifier: %s\n", line), 1);
		i++;
	}
	return (0);
}
