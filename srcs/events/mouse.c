/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:45:23 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/26 02:17:10 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @fn int handle_mouse_event(int button, int x, int y, t_fractal *frac)
 * @brief Hooks into MLX mouse events.
 * @details Triggers center-screen zooming and requests a re-render.
 * @param button The mouse button pressed.
 * @param x      X-coordinate of the mouse (unused).
 * @param y      Y-coordinate of the mouse (unused).
 * @param frac   Pointer to the main fractal structure.
 * @return       EXIT_SUCCESS.
 */
int	handle_mouse_event(int button, int x, int y, t_fractal *frac)
{
	(void)x;
	(void)y;
	if (button == MOUSE_SCROLL_UP && frac->zoom > ZOOM_MIN)
		frac->zoom *= ZOOM_SCALE;
	else if (button == MOUSE_SCROLL_DOWN && frac->zoom < ZOOM_MAX)
		frac->zoom /= ZOOM_SCALE;
	else
		return (EXIT_SUCCESS);
	render(frac);
	return (EXIT_SUCCESS);
}
