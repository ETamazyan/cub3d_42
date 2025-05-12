/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:42:47 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/11 22:20:50 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str, int i, int flag)
{
	int	num;
	int	sign;

	num = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		flag = 1;
		num = num * 10;
		num += str[i] - '0';
		i++;
	}
	if (flag == 1)
		return (num * sign);
	return (-1);
}

/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
	int val;
	char str[20];

	strcpy(str, "--0000098993489");
	val = ft_atoi(str);
	printf("MY String value = %s, MY Int value = %d\n", str, val);
	val = atoi(str);
	printf("String value = %s, Int value = %d\n", str, val);

	return(0);
}*/
