/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 01:01:30 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/27 15:38:30 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @fn void julia(t_fractal *frac)
 * @brief Calculates iterations for the Julia set.
 * @details Applies the formula Z = Z^2 + C, where C is a constant provided by 
 * the user, until it escapes the bounds or reaches max iterations.
 * @param frac Pointer to the main fractal structure.
 */
void	julia(t_fractal *frac)
{
	double	tmp;

	frac->z.re = ((XMAX - XMIN) * (double)frac->x / frac->disp.width + XMIN)
		* frac->zoom + frac->off_x;
	frac->z.im = (YMAX - (YMAX - YMIN) * (double)frac->y / frac->disp.height)
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
