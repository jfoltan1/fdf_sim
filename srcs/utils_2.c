/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 13:32:18 by jfoltan           #+#    #+#             */
/*   Updated: 2023/11/23 18:22:02 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	free_arr(char **array)
{
	int	i;

	i = 0;
	if (!array[i])
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_points(t_points *points)
{
	t_points	*temp;

	if (points)
	{
		while (points->next != NULL)
		{
			temp = points;
			points = points->next;
			free(temp);
		}
		temp = points;
		free(temp);
	}
}

int	init_fd(char *name)
{
	int	fd;
	int	a;

	fd = -1;
	a = ft_strlen(name) - 1;
	if (name[a] == 'f')
		if (name[a - 1] == 'd')
			if (name[a - 2] == 'f')
				if (name[a - 3] == '.')
					fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("dum dum file no good\n", 1);
		exit(1);
	}
	return (fd);
}

int	get_len_of_map(char *line, int fd)
{
	int	a;

	a = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			free(line);
			break ;
		}
		free(line);
		a++;
	}
	close(fd);
	return (a);
}

void	draw_line_loop(t_vars *vars, t_help_points first_point,
		t_draw_points projected_points, int color)
{
	int		err;
	int		e2;

	err = first_point.dx - first_point.dy;
	while (1)
	{
		my_mlx_pixel_put(*vars, projected_points.x1, projected_points.y1,
			color);
		if (projected_points.x1 == projected_points.x2
			&& projected_points.y1 == projected_points.y2)
			break ;
		e2 = 2 * err;
		if (e2 > -first_point.dy)
		{
			err -= first_point.dy;
			projected_points.x1 += first_point.sx;
		}
		if (e2 < first_point.dx)
		{
			err += first_point.dx;
			projected_points.y1 += first_point.sy;
		}
	}
}
