/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 01:20:16 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/26 01:27:52 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @fn void mandelbrot(t_fractal *frac)
 * @brief Calculates iterations for the Mandelbrot set.
 * @details Applies the standard formula Z = Z^2 + C, where C is the current 
 * pixel coordinate, until it escapes the bounds or reaches max iterations.
 * @param frac Pointer to the main fractal structure.
 */
void	mandelbrot(t_fractal *frac)
{
	double	tmp;

	frac->z.re = 0.0;
	frac->z.im = 0.0;
	frac->c.re = ((XMAX - XMIN) * (double)frac->x / frac->disp.width + XMIN)
		* frac->zoom + frac->off_x;
	frac->c.im = ((YMAX - YMIN) * (double)frac->y / frac->disp.height + YMIN)
		* frac->zoom + frac->off_y;
	frac->iter = -1;
	while (++frac->iter < frac->max_iter
		&& frac->z.re * frac->z.re + frac->z.im * frac->z.im <= FRAC_LIMIT)
	{
		tmp = frac->z.re * frac->z.re - frac->z.im * frac->z.im + frac->c.re;
		frac->z.im = 2.0 * frac->z.re * frac->z.im + frac->c.im;
		frac->z.re = tmp;
	}
}
