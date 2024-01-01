/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:22:42 by jfoltan           #+#    #+#             */
/*   Updated: 2023/11/23 18:25:06 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <sys/stat.h>
# include <sys/types.h>

typedef struct s_points
{
	long		x_pos;
	long		y_pos;
	long		z_pos;
	void		*head;
	int			color;
	void		*next;
	long		column;
	long		row;
}				t_points;

typedef struct s_vars
{
	t_points	*points;
	void		*mlx;
	void		*win;
	void		*img;
	void		*data;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			x;
	int			y;

}				t_vars;

typedef struct s_map
{
	int			fd;
	int			a;
	char		**array;
	char		*line;
}				t_map;

typedef struct s_iso
{
	double	angle_radians;
	double	zoom;
	int		offset_x;
	int		offset_y;
	double	scaled_x;
	double	scaled_y;
	double	scaled_z;
	double	projected_x;
	double	projected_y;
}	t_iso;

typedef struct s_help_points
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
}	t_help_points;

typedef struct s_draw_points
{
	int	x1;
	int	y1;
	int	x2; 
	int	y2;
}	t_draw_points;
typedef struct s_literally_peaking_rn
{
	int		x;
	int		y;
}	t_peak;
int				init_fd(char *name);
void			arg_check(int argc);
void			format_string(char *input);
void			get_rid_of_space(char *line);
int				get_len_of_map(char *line, int fd);
t_points		*iso(t_points *points, int size_x, int size_y);
t_points		*parser(t_points *points, char **array, int *max_x, int *max_y);
int				find_char(char *str, char findme);
t_points		*scale_me_daddy(t_points *points, int *max_x, int *max_y);
void			draw_line(t_vars *vars, t_draw_points projected_points,
					int color);
void			draw_lines_vertical(t_points *points, t_vars vars);
char			*get_next_line(int fd);
void			free_arr(char **array);
void			draw_lines_horizontal(t_points *points, t_vars vars);
void			free_points(t_points *points);
void			append_point(t_points **points, t_points *new_point,
					t_points **head);
void			draw_line_loop(t_vars *vars, t_help_points first_point,
					t_draw_points projected_points, int color);
void			my_mlx_pixel_put(t_vars vars, int x, int y, int color);

#endif