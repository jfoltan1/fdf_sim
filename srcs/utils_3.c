/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:19:22 by jfoltan           #+#    #+#             */
/*   Updated: 2023/11/23 18:22:53 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	append_point(t_points **points, t_points *new_point, t_points **head)
{
	if (*points == NULL)
	{
		*points = new_point;
		*head = *points;
	}
	else
	{
		(*points)->next = new_point;
		*points = (*points)->next;
	}
}

void	get_rid_of_space(char *line)
{
	int		i; 

	i = ft_strlen(line) - 1;
	while (line[i] == ' ' || line[i] == '\n')
		i--;
	line[i + 1] = '\0';
}

void	format_string(char *input)
{
	int		len;
	int		index;
	int		i;

	len = ft_strlen(input);
	index = 0;
	i = 0;
	while (i < len)
	{
		if (input[i] == ' ')
		{
			while (input[i] == ' ')
				++i;
			input[index++] = ' ';
		}
		input[index++] = input[i++];
	}
	input[index] = '\0';
	get_rid_of_space(input);
}

void	arg_check(int argc)
{
	if (argc == 1 || argc > 2)
	{
		ft_putstr_fd("Improper arguments!\n", 1);
		ft_putstr_fd("Program expects path to map as only argument!\n", 1);
		exit(1);
	}
}
