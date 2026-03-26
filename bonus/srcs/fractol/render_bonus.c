/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 01:42:31 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/26 03:13:08 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

/**
 * @fn static void apply_shade(t_fractal *frac)
 * @brief Applies brightness or grayscale shading to the computed color.
 * @details Modifies the RGB channels based on the current shade multiplier or 
 * toggles grayscale.
 * @param frac Pointer to the main fractal structure.
 */
static void	apply_shade(t_fractal *frac)
{
	int				gray;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;

	if (frac->is_gray)
	{
		gray = (int)((double)frac->iter / frac->max_iter * 255);
		frac->color = (gray << 16) | (gray << 8) | gray;
		return ;
	}
	red = (unsigned char)(((frac->color >> 16) & 0xff) * frac->shade);
	green = (unsigned char)(((frac->color >> 8) & 0xff) * frac->shade);
	blue = (unsigned char)((frac->color & 0xff) * frac->shade);
	frac->color = (red << 16) | (green << 8) | blue;
}

/**
 * @fn static void apply_pixel_color(t_fractal *frac)
 * @brief Determines the final color for a pixel based on iterations.
 * @details Sets to black if inside the set (max_iter reached), otherwise 
 * fetches color from the active palette.
 * @param frac Pointer to the main fractal structure.
 */
static void	apply_pixel_color(t_fractal *frac)
{
	if (frac->iter == frac->max_iter)
	{
		frac->color = 0x000000;
		return ;
	}
	else if (!frac->is_gray)
		frac->color = frac->palette[frac->palette_idx](frac->iter,
				frac->max_iter);
	apply_shade(frac);
}

/**
 * @fn static void ft_mlx_pixel_put(const t_fractal *frac)
 * @brief Writes a color to a specific pixel in the MLX image buffer.
 * @details Calculates the memory offset for (x, y) and applies the integer 
 * color value directly.
 * @param frac Pointer to the main fractal structure (read-only).
 */
static void	ft_mlx_pixel_put(const t_fractal *frac)
{
	char	*dst;

	if (frac->x < 0 || frac->y < 0 || frac->x >= frac->disp.width
		|| frac->y >= frac->disp.height)
		return ;
	dst = frac->disp.data.addr + (frac->y * frac->disp.data.line_len
			+ frac->x * (frac->disp.data.bpp / 8));
	*(unsigned int *)dst = frac->color;
}

/**
 * @fn void render(t_fractal *frac)
 * @brief Renders the entire fractal frame.
 * @details Iterates over every pixel, computes the fractal algorithm, applies 
 * coloring, and pushes the image to the window.
 * @param frac Pointer to the main fractal structure.
 */
void	render(t_fractal *frac)
{
	frac->x = -1;
	while (++(frac->x) < frac->disp.width)
	{
		frac->y = -1;
		while (++(frac->y) < frac->disp.height)
		{
			if (frac->type == MANDELBROT_TYPE)
				mandelbrot(frac);
			else if (frac->type == JULIA_TYPE)
				julia(frac);
			else if (frac->type == TRICORN_TYPE)
				tricorn(frac);
			else if (frac->type == BURNING_SHIP_TYPE)
				burning_ship(frac);
			else if (frac->type == PHOENIX_TYPE)
				phoenix(frac);
			else
				phoenix_variant(frac);
			apply_pixel_color(frac);
			ft_mlx_pixel_put(frac);
		}
	}
	mlx_put_image_to_window(frac->disp.mlx, frac->disp.win,
		frac->disp.data.img, 0, 0);
}
