/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:01:31 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/26 03:07:54 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @fn static void malloc_error(t_display *disp)
 * @brief Handles memory allocation failures gracefully.
 * @details Destroys MLX pointers if they exist and exits the program with a 
 * failure status.
 * @param disp Pointer to the display structure containing MLX pointers.
 */
static void	malloc_error(t_display *disp)
{
	if (disp->mlx)
	{
		if (disp->win)
			mlx_destroy_window(disp->mlx, disp->win);
		mlx_destroy_display(disp->mlx);
		free (disp->mlx);
	}
	ft_putendl_fd("Error: Memory allocation or MLX setup failed!",
		STDERR_FILENO);
	exit(EXIT_FAILURE);
}

/**
 * @fn static void set_resolution(t_fractal *frac)
 * @brief Prompts the user to set the window resolution via standard input.
 * @details Reads a line from STDIN, strictly parses it ignoring spaces, 
 * and sets width and height. Defaults to 800x600 on invalid input.
 * @param frac Pointer to the main fractal structure.
 */
static void	set_resolution(t_fractal *frac)
{
	char	*line;
	char	*tmp;
	int		c;

	line = get_next_line(STDIN_FILENO);
	tmp = line;
	while (tmp && (ft_isspace(*tmp)))
		tmp++;
	c = 0;
	if (tmp && *tmp)
		c = *tmp++ - '0';
	while (tmp && (ft_isspace(*tmp)))
		tmp++;
	if (tmp && (*tmp == '\n' || *tmp == '\0') && c >= 1 && c <= 4)
	{
		frac->disp.width = WIDTH_800 * (c == 1) + WIDTH_1024 * (c == 2)
			+ WIDTH_1280 * (c == 3) + WIDTH_1680 * (c == 4);
		frac->disp.height = HEIGHT_600 * (c == 1) + HEIGHT_768 * (c == 2)
			+ HEIGHT_720 * (c == 3) + HEIGHT_1050 * (c == 4);
	}
	else
		ft_putendl_fd("Invalid/no input. Default applied!", STDOUT_FILENO);
	free(line);
}

/**
 * @fn int blue_orange_palette(int iter, int max_iter)
 * @brief Generates a specific color based on the current iteration.
 * @details Uses trigonometric or polynomial functions to smoothly interpolate 
 * RGB values.
 * @param iter     The current iteration count for a pixel.
 * @param max_iter The maximum iterations allowed.
 * @return         The calculated color as an integer (0xRRGGBB).
 */
static int	blue_orange_palette(int iter, int max_iter)
{
	double	tmp;
	int		red;
	int		green;
	int		blue;

	tmp = (double)iter / max_iter;
	red = (int)(9 * (1 - tmp) * tmp * tmp * tmp * 255);
	green = (int)(15 * (1 - tmp) * (1 - tmp) * tmp * tmp * 255);
	blue = (int)(8.5 * (1 - tmp) * (1 - tmp) * (1 - tmp) * tmp * 255);
	return ((red << 16) | (green << 8) | blue);
}

/**
 * @fn static void set_default_values(t_fractal *frac)
 * @brief Initializes default mathematical and visual values for the fractal.
 * @details Sets defaults for iterations, offset, zoom, and assigns the 
 * color palette.
 * @param frac Pointer to the main fractal structure.
 */
static void	set_default_values(t_fractal *frac)
{
	frac->disp.mlx = NULL;
	frac->disp.win = NULL;
	frac->disp.data.img = NULL;
	frac->disp.width = WIDTH_800;
	frac->disp.height = HEIGHT_600;
	frac->max_iter = ITER_INIT;
	frac->off_x = OFF_X_INIT;
	frac->off_y = OFF_Y_INIT;
	frac->zoom = ZOOM_INIT;
	frac->palette = blue_orange_palette;
}

/**
 * @fn void init(t_fractal *frac)
 * @brief Sets up the MLX environment and prepares the fractal struct.
 * @details Handles MLX initialization, window creation, and image buffer 
 * allocation.
 * @param frac Pointer to the main fractal structure.
 */
void	init(t_fractal *frac)
{
	ft_putendl_fd("Available fractal resolutions:\n", STDOUT_FILENO);
	ft_putendl_fd("\t1 - 800 * 600 (default)", STDOUT_FILENO);
	ft_putendl_fd("\t2 - 1024 * 768", STDOUT_FILENO);
	ft_putendl_fd("\t3 - 1280 * 720", STDOUT_FILENO);
	ft_putendl_fd("\t4 - 1680 * 1050\n", STDOUT_FILENO);
	ft_putstr_fd("Please select one: ", STDOUT_FILENO);
	set_default_values(frac);
	set_resolution(frac);
	frac->disp.mlx = mlx_init();
	if (!frac->disp.mlx)
		malloc_error(&frac->disp);
	frac->disp.win = mlx_new_window(frac->disp.mlx, frac->disp.width,
			frac->disp.height, frac->disp.name);
	if (!frac->disp.win)
		malloc_error(&frac->disp);
	frac->disp.data.img = mlx_new_image(frac->disp.mlx, frac->disp.width,
			frac->disp.height);
	if (!frac->disp.data.img)
		malloc_error(&frac->disp);
	frac->disp.data.addr = mlx_get_data_addr(frac->disp.data.img,
			&frac->disp.data.bpp, &frac->disp.data.line_len,
			&frac->disp.data.endian);
}
