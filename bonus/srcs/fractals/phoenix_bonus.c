/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phoenix_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 00:59:43 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/29 13:46:49 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

/**
 * @fn void phoenix(t_fractal *frac)
 * @brief Calculates iterations for the standard Phoenix fractal.
 * @details Uses a recurrence relation relying on the previous iteration: 
 * Z_n+1 = Z_n^2 + C + delta * Z_n-1.
 * @param frac Pointer to the main fractal structure.
 */
void	phoenix(t_fractal *frac)
{
	double	prev_re;
	double	prev_im;
	double	curr_re;
	double	curr_im;

	frac->z.re = (YMAX - (YMAX - YMIN) * (double)frac->y / frac->disp.height)
		* frac->zoom - frac->off_y;
	frac->z.im = ((XMAX - XMIN) * (double)frac->x / frac->disp.width + XMIN)
		* frac->zoom + frac->off_x;
	prev_re = 0.0;
	prev_im = 0.0;
	frac->iter = -1;
	while (++frac->iter < frac->max_iter
		&& frac->z.re * frac->z.re + frac->z.im * frac->z.im <= FRAC_LIMIT)
	{
		curr_re = frac->z.re;
		curr_im = frac->z.im;
		frac->z.re = curr_re * curr_re - curr_im * curr_im + frac->c.re
			+ frac->delta * prev_re;
		frac->z.im = 2.0 * curr_re * curr_im + frac->c.im
			+ frac->delta * prev_im;
		prev_re = curr_re;
		prev_im = curr_im;
	}
}
