/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:34:41 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/26 02:05:50 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @fn static void update_iterations(int keysym, t_fractal *frac)
 * @brief Adjusts the maximum depth/iterations via keyboard.
 * @details Increases or decreases max_iter to add or reduce fractal detail.
 * @param keysym The keycode pressed.
 * @param frac   Pointer to the main fractal structure.
 */
static void	update_iterations(int keysym, t_fractal *frac)
{
	if (keysym == XK_q)
	{
		frac->max_iter -= ITER_SCALE;
		if (frac->max_iter < ITER_MIN)
			frac->max_iter = ITER_MIN;
	}
	if (keysym == XK_e)
	{
		frac->max_iter += ITER_SCALE;
		if (frac->max_iter > ITER_MAX)
			frac->max_iter = ITER_MAX;
	}
}

/**
 * @fn int handle_key_event(int keysym, t_fractal *frac)
 * @brief Main keyboard event router.
 * @details Catches ESC to exit, delegates other keys to sub-handlers, and 
 * re-renders the image.
 * @param keysym The keycode pressed.
 * @param frac   Pointer to the main fractal structure.
 * @return       EXIT_SUCCESS.
 */
int	handle_key_event(int keysym, t_fractal *frac)
{
	if (keysym == XK_Escape)
		exit_program(&frac->disp);
	update_iterations(keysym, frac);
	render(frac);
	return (EXIT_SUCCESS);
}
