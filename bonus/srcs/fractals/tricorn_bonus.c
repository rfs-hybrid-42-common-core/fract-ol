/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricorn_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 00:58:07 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/26 03:10:45 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

/**
 * @fn void tricorn(t_fractal *frac)
 * @brief Calculates iterations for the Tricorn fractal.
 * @details Uses the conjugated formula Z = (conj(Z))^2 + C.
 * @param frac Pointer to the main fractal structure.
 */
void	tricorn(t_fractal *frac)
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
		frac->z.im = -2.0 * frac->z.re * frac->z.im + frac->c.im;
		frac->z.re = tmp;
	}
}
