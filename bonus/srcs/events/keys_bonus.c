/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:34:41 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/27 15:27:17 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

/**
 * @fn static void update_phoenix_delta(int keysym, t_fractal *frac)
 * @brief Adjusts the delta parameter for Phoenix fractals via keyboard.
 * @details Modifies the delta value using the bracket keys and clamps it 
 * securely between DELTA_MIN and DELTA_MAX.
 * @param keysym The keycode pressed.
 * @param frac   Pointer to the main fractal structure.
 */
static void	update_phoenix_delta(int keysym, t_fractal *frac)
{
	if (frac->type == PHOENIX_TYPE || frac->type == PHOENIX_VARIANT_TYPE)
	{
		if (keysym == XK_bracketleft)
		{
			frac->delta -= DELTA_SCALE;
			if (frac->delta < DELTA_MIN)
				frac->delta = DELTA_MIN;
		}
		if (keysym == XK_bracketright)
		{
			frac->delta += DELTA_SCALE;
			if (frac->delta > DELTA_MAX)
				frac->delta = DELTA_MAX;
		}
	}
}

/**
 * @fn static void apply_color_shade(int keysym, t_fractal *frac)
 * @brief Handles keyboard inputs related to coloring.
 * @details Switches palettes, toggles grayscale, and adjusts shading intensity.
 * @param keysym The keycode pressed.
 * @param frac   Pointer to the main fractal structure.
 */
static void	apply_color_shade(int keysym, t_fractal *frac)
{
	if (keysym == XK_Page_Up && !frac->is_gray)
		frac->palette_idx = (frac->palette_idx + 1) % frac->n_palettes;
	if (keysym == XK_Page_Down && !frac->is_gray)
	{
		if (frac->palette_idx == 0)
			frac->palette_idx = frac->n_palettes;
		frac->palette_idx = (frac->palette_idx - 1) % frac->n_palettes;
	}
	if (keysym == XK_g)
		frac->is_gray = !frac->is_gray;
	if (keysym == XK_Home)
	{
		frac->shade += SHADE_SCALE;
		if (frac->shade > SHADE_MAX)
			frac->shade = SHADE_MAX;
	}
	if (keysym == XK_End)
	{
		frac->shade -= SHADE_SCALE;
		if (frac->shade < SHADE_MIN)
			frac->shade = SHADE_MIN;
	}
}

/**
 * @fn static void screen_padding_zoom(int keysym, t_fractal *frac)
 * @brief Handles keyboard inputs for navigation.
 * @details Translates the view (arrows/WASD), zooms (plus/minus), and resets 
 * the view (R).
 * @param keysym The keycode pressed.
 * @param frac   Pointer to the main fractal structure.
 */
static void	screen_padding_zoom(int keysym, t_fractal *frac)
{
	if (keysym == XK_w || keysym == XK_Up)
		frac->off_y -= PADDING_SCALE * frac->zoom;
	if (keysym == XK_s || keysym == XK_Down)
		frac->off_y += PADDING_SCALE * frac->zoom;
	if (keysym == XK_a || keysym == XK_Left)
		frac->off_x -= PADDING_SCALE * frac->zoom;
	if (keysym == XK_d || keysym == XK_Right)
		frac->off_x += PADDING_SCALE * frac->zoom;
	if ((keysym == XK_plus || keysym == XK_KP_Add) && frac->zoom > ZOOM_MIN)
		frac->zoom *= ZOOM_SCALE;
	if ((keysym == XK_minus || keysym == XK_KP_Subtract)
		&& frac->zoom < ZOOM_MAX)
		frac->zoom /= ZOOM_SCALE;
	if (keysym == XK_r)
	{
		frac->shade = SHADE_INIT;
		frac->max_iter = ITER_INIT;
		frac->off_x = OFF_X_INIT;
		frac->off_y = OFF_Y_INIT;
		frac->zoom = ZOOM_INIT;
		frac->is_gray = false;
		frac->palette_idx = PALETTE_INIT % frac->n_palettes;
	}
}

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
	update_phoenix_delta(keysym, frac);
	apply_color_shade(keysym, frac);
	screen_padding_zoom(keysym, frac);
	update_iterations(keysym, frac);
	render(frac);
	return (EXIT_SUCCESS);
}
