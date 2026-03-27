/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:01:31 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/27 18:41:53 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

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
 * @fn static void set_palettes(t_fractal *frac)
 * @brief Populates the palette array with function pointers.
 * @details Assigns available color generation functions to the palette array 
 * and sets the initial index.
 * @param frac Pointer to the main fractal structure.
 */
static void	set_palettes(t_fractal *frac)
{
	frac->palette[0] = blue_orange_palette;
	frac->palette[1] = lava_lamp_palette;
	frac->palette[2] = neon_cyberpunk_palette;
	frac->palette[3] = phoenix_glow_palette;
	frac->palette[4] = hsv_palette;
	frac->palette[5] = autumn_palette;
	frac->palette[6] = autumn_frost_palette;
	frac->palette[7] = tropical_sunset_palette;
	frac->palette[8] = winter_sunrise_palette;
	frac->palette[9] = funky_galaxy_palette;
	frac->n_palettes = PALETTE_TOTAL;
	frac->palette_idx = PALETTE_INIT % frac->n_palettes;
}

/**
 * @fn static void set_default_values(t_fractal *frac)
 * @brief Initializes default mathematical and visual values for the fractal.
 * @details Sets defaults for iterations, offset, zoom, shading, and 
 * initializes the palettes.
 * @param frac Pointer to the main fractal structure.
 */
static void	set_default_values(t_fractal *frac)
{
	frac->disp.mlx = NULL;
	frac->disp.win = NULL;
	frac->disp.data.img = NULL;
	frac->disp.width = WIDTH_800;
	frac->disp.height = HEIGHT_600;
	frac->shade = SHADE_INIT;
	frac->max_iter = ITER_INIT;
	frac->off_x = OFF_X_INIT;
	frac->off_y = OFF_Y_INIT;
	frac->zoom = ZOOM_INIT;
	frac->is_gray = false;
	set_palettes(frac);
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
