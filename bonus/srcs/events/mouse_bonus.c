/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:45:23 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/26 03:19:58 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

/**
 * @fn static void screen_zoom(int button, int x, int y, t_fractal *frac)
 * @brief Adjusts the complex plane offset so the zoom follows the mouse cursor.
 * @details Calculates the complex coordinate before zooming and adjusts the 
 * offset to keep that coordinate under the cursor after zooming.
 * @param button The mouse button pressed.
 * @param x      X-coordinate of the mouse.
 * @param y      Y-coordinate of the mouse.
 * @param frac   Pointer to the main fractal structure.
 */
static void	screen_zoom(int button, int x, int y, t_fractal *frac)
{
	double	prev_off_re;
	double	prev_off_im;

	prev_off_re = ((XMAX - XMIN) * (double)x / frac->disp.width + XMIN)
		* frac->zoom + frac->off_x;
	prev_off_im = ((YMAX - YMIN) * (double)y / frac->disp.height + YMIN)
		* frac->zoom + frac->off_y;
	if (button == MOUSE_SCROLL_UP)
		frac->zoom *= ZOOM_SCALE;
	if (button == MOUSE_SCROLL_DOWN)
		frac->zoom /= ZOOM_SCALE;
	frac->off_x = prev_off_re - ((XMAX - XMIN) * x / frac->disp.width + XMIN)
		* frac->zoom;
	frac->off_y = prev_off_im - ((YMAX - YMIN) * y / frac->disp.height + YMIN)
		* frac->zoom;
}

/**
 * @fn int handle_mouse_event(int button, int x, int y, t_fractal *frac)
 * @brief Hooks into MLX mouse events.
 * @details Triggers zooming and requests a re-render.
 * @param button The mouse button pressed.
 * @param x      X-coordinate of the mouse.
 * @param y      Y-coordinate of the mouse.
 * @param frac   Pointer to the main fractal structure.
 * @return       EXIT_SUCCESS.
 */
int	handle_mouse_event(int button, int x, int y, t_fractal *frac)
{
	if ((button == MOUSE_SCROLL_UP && frac->zoom > ZOOM_MIN)
		|| (button == MOUSE_SCROLL_DOWN && frac->zoom < ZOOM_MAX))
		screen_zoom(button, x, y, frac);
	else
		return (EXIT_SUCCESS);
	render(frac);
	return (EXIT_SUCCESS);
}
