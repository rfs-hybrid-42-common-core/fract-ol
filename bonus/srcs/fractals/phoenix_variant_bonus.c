/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phoenix_variant_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 01:07:04 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/26 03:10:39 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

/**
 * @fn void phoenix_variant(t_fractal *frac)
 * @brief Calculates iterations for a variant of the Phoenix fractal.
 * @details Modifies the imaginary calculation of the standard Phoenix set for 
 * a different visual output.
 * @param frac Pointer to the main fractal structure.
 */
void	phoenix_variant(t_fractal *frac)
{
	double	tmp;
	double	prev_re;
	double	prev_im;

	frac->z.re = ((YMAX - YMIN) * (double)frac->y / frac->disp.height + YMIN)
		* frac->zoom + frac->off_y;
	frac->z.im = ((XMAX - XMIN) * (double)frac->x / frac->disp.width + XMIN)
		* frac->zoom + frac->off_x;
	prev_re = frac->z.re;
	prev_im = frac->z.im;
	frac->iter = -1;
	while (++frac->iter < frac->max_iter
		&& frac->z.re * frac->z.re + frac->z.im * frac->z.im <= FRAC_LIMIT)
	{
		tmp = frac->z.re * frac->z.re - frac->z.im * frac->z.im
			+ frac->c.re + frac->delta * prev_re;
		prev_im = frac->z.im;
		frac->z.im = 2.0 * frac->z.re * frac->z.im + frac->delta * prev_im;
		prev_re = frac->z.re;
		frac->z.re = tmp;
	}
}
