/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 13:25:28 by jfoltan           #+#    #+#             */
/*   Updated: 2023/11/24 13:38:53 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	my_mlx_pixel_put(t_vars vars, int x, int y, int color)
{
	char	*dst;

	(void)color;
	if (x > 0 && y > 0 && x < 1280 && y < 720)
	{
		dst = vars.data + (y * vars.size_line + x * (vars.bits_per_pixel / 8));
		*(int *)dst = color;
	}
}

t_points	*iso(t_points *points, int size_x, int size_y)
{
	void	*head;
	t_iso	iso;

	iso.angle_radians = 0.785398;
	iso.zoom = 10;
	iso.offset_x = 1280 / 2;
	iso.offset_y = 720 / 2;
	head = points;
	while (points != NULL)
	{
		iso.scaled_x = (points->x_pos - size_x / 2) * iso.zoom;
		iso.scaled_y = (points->y_pos - size_y / 2) * iso.zoom;
		iso.scaled_z = points->z_pos * iso.zoom * 4 / 10;
		iso.projected_x = (iso.scaled_x - iso.scaled_y) * cos(iso.angle_radians)
			+ iso.offset_x;
		iso.projected_y = (iso.scaled_x + iso.scaled_y) * sin(iso.angle_radians)
			- iso.scaled_z + iso.offset_y;
		points->x_pos = (int)iso.projected_x;
		points->y_pos = (int)iso.projected_y;
		points = points->next;
	}
	return (head);
}

void	draw_line(t_vars *vars, t_draw_points projected_points, int color)
{
	t_help_points	first_point;

	first_point.dx = abs(projected_points.x2 - projected_points.x1);
	first_point.dy = abs(projected_points.y2 - projected_points.y1);
	if (projected_points.x1 < projected_points.x2)
		first_point.sx = 1;
	else
		first_point.sx = -1;
	if (projected_points.y1 < projected_points.y2)
		first_point.sy = 1;
	else
		first_point.sy = -1;
	draw_line_loop(vars, first_point, projected_points, color);
}

void	draw_lines_vertical(t_points *points, t_vars vars)
{
	t_points		*temp;
	t_draw_points	projected_points;
	t_points		*head;

	head = points;
	temp = points;
	while (temp && temp->column <= points->column)
		temp = temp->next;
	while (points != NULL)
	{
		projected_points.x1 = points->x_pos;
		projected_points.y1 = points->y_pos;
		if (points->next)
		{
			projected_points.x2 = temp->x_pos;
			projected_points.y2 = temp->y_pos;
			draw_line(&vars, projected_points, points->color);
		}
		points = points->next;
		if (temp->next != NULL)
			temp = temp->next;
		else
			break ;
	}
	points = head;
}

void	draw_lines_horizontal(t_points *points, t_vars vars)
{
	t_draw_points	projected_points;
	t_points		*head;

	head = points;
	while (points != NULL)
	{
		projected_points.x1 = points->x_pos;
		projected_points.y1 = points->y_pos;
		if (points->next
			&& points->column == ((t_points *)(points->next))->column)
		{
			projected_points.x2 = ((t_points *)(points->next))->x_pos;
			projected_points.y2 = ((t_points *)(points->next))->y_pos;
			draw_line(&vars, projected_points, points->color);
		}
		points = points->next;
	}
	points = head;
}
