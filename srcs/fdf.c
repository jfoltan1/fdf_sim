/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 13:13:34 by jfoltan           #+#    #+#             */
/*   Updated: 2023/11/23 18:57:14 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	get_out_on_key(int keycode, t_vars *vars)
{
	if (keycode == 65307)
	{
		mlx_destroy_image(vars->mlx, vars->img);
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		free_points(vars->points);
		free(vars->mlx);
		free(vars);
		exit(0);
	}
	return (0);
}

int	get_out(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free_points(vars->points);
	free(vars->mlx);
	free(vars);
	exit(0);
}

t_vars	*init_vars(void)
{
	t_vars	*vars;

	vars = ft_calloc(1, sizeof(t_vars));
	vars->bits_per_pixel = 256;
	vars->endian = 1;
	vars->size_line = 1280 * (256 / 8);
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, 1280, 720, "fdf my guy is FAAAAB");
	if (vars->mlx == NULL || vars->win == NULL)
	{
		free(vars->mlx);
		free(vars->win);
		exit(1);
	}
	vars->img = mlx_new_image(vars->mlx, 1280, 720);
	vars->data = mlx_get_data_addr(vars->img, &vars->bits_per_pixel,
			&vars->size_line, &vars->endian);
	vars->x = 0;
	vars->y = 0;
	return (vars);
}

char	**get_map(char *name, int fd)
{
	int		a;
	char	**array;
	char	*line;

	a = 0;
	a = get_len_of_map(name, fd);
	array = ft_calloc(a + 1, sizeof(char **));
	fd = open(name, O_RDONLY);
	a = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		format_string(line);
		array[a] = ft_strdup(line);
		free(line);
		a++;
	}
	free(line);
	return (array);
}

int	main(int argc, char **argv)
{
	t_vars	*vars;
	t_map	map;
	int		fd;
	int		size_x;
	int		size_y;

	arg_check(argc);
	fd = init_fd(argv[1]);
	map.array = get_map(argv[1], fd);
	vars = init_vars();
	size_x = 0;
	size_y = 0;
	vars->points = parser(vars->points, map.array, &size_x, &size_y);
	free_arr(map.array);
	vars->points = iso(vars->points, size_x, size_y);
	draw_lines_vertical(vars->points, *vars);
	draw_lines_horizontal(vars->points, *vars);
	mlx_hook(vars->win, 17, 1L << 17, get_out, vars);
	mlx_hook(vars->win, 2, 1L << 0, get_out_on_key, vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	mlx_loop(vars->mlx);
	return (0);
}
