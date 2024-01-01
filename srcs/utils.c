/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 13:11:19 by jfoltan           #+#    #+#             */
/*   Updated: 2023/11/24 13:43:42 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	hex_char_to_int(char c)
{
	if (c >= '0' && c <= '9')
	{
		return (c - '0');
	}
	else if (c >= 'A' && c <= 'F')
	{
		return (10 + (c - 'A'));
	}
	else if (c >= 'a' && c <= 'f')
	{
		return (10 + (c - 'a'));
	}
	else
	{
		return (-1);
	}
}

int	hex_to_int(char *hex)
{
	int		result;
	int		digit;
	int		i;

	i = 0;
	result = 0;
	while (hex[i] != ',')
		i++;
	if (hex[i + 1] == '0' && (hex[i + 2] == 'x' || hex[i + 2] == 'X'))
		i += 3;
	while (hex[i])
	{
		digit = hex_char_to_int(hex[i]);
		if (digit == -1)
			return (-1);
		result = (result << 4) | digit;
		i++;
	}
	return (result);
}

int	find_char(char *str, char findme)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == findme)
			return (i + 1);
		i++;
	}
	return (0);
}

t_points	*add_point(char *line, int x, int y)
{
	t_points	*new_point;

	new_point = ft_calloc(1, sizeof(t_points));
	if (!new_point)
		return (NULL);
	new_point->x_pos = x;
	new_point->y_pos = y;
	new_point->z_pos = ft_atoi(line);
	if (find_char(line, ',') != 0)
		new_point->color = hex_to_int(line);
	else
		new_point->color = 0xFFFFFF;
	new_point->next = NULL;
	new_point->column = y;
	return (new_point);
}

t_points	*parser(t_points *points, char **array, int *max_x, int *max_y)
{
	t_points	*head;
	int			y;
	char		**line_split;
	int			x;
	t_points	*new_point;

	head = NULL;
	y = -1;
	while (array[++y])
	{
		line_split = ft_split(array[y], ' ');
		x = 0;
		while (line_split[x] != NULL)
		{
			new_point = add_point(line_split[x], x, y);
			append_point(&points, new_point, &head);
			if (*max_x < x)
				*max_x = x;
			x++;
		}
		free_arr(line_split);
	}
	*max_x += 1;
	*max_y = y;
	return (head);
}
