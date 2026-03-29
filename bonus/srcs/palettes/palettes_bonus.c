/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palettes_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:38:52 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/28 21:32:00 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

/**
 * @fn int blue_orange_palette(int iter, int max_iter)
 * @brief Generates a specific color based on the current iteration.
 * @details Uses trigonometric or polynomial functions to smoothly interpolate 
 * RGB values.
 * @param iter     The current iteration count for a pixel.
 * @param max_iter The maximum iterations allowed.
 * @return         The calculated color as an integer (0xRRGGBB).
 */
int	blue_orange_palette(int iter, int max_iter)
{
	double	tmp;
	int		red;
	int		green;
	int		blue;

	tmp = (double)iter / max_iter;
	red = (int)(9 * (1 - tmp) * tmp * tmp * tmp * 255);
	green = (int)(15 * (1 - tmp) * (1 - tmp) * tmp * tmp * 255);
	blue = (int)(8.5 * (1 - tmp) * (1 - tmp) * (1 - tmp) * tmp * 255);
	return ((red << 16) | (green << 8) | blue);
}

/**
 * @fn int inferno_palette(int iter, int max_iter)
 * @brief Generates a specific color based on the current iteration.
 * @details Uses trigonometric or polynomial functions to smoothly interpolate 
 * RGB values.
 * @param iter     The current iteration count for a pixel.
 * @param max_iter The maximum iterations allowed.
 * @return         The calculated color as an integer (0xRRGGBB).
 */
int	inferno_palette(int iter, int max_iter)
{
	double	tmp;
	int		red;
	int		green;
	int		blue;

	tmp = (double)iter / max_iter;
	red = (int)(255 * sqrt(sin(tmp * 3.14159)));
	green = (int)(255 * tmp * tmp * tmp);
	blue = (int)(255 * tmp * tmp * tmp * tmp * tmp);
	return ((red << 16) | (green << 8) | blue);
}

/**
 * @fn int neon_cyberpunk_palette(int iter, int max_iter)
 * @brief Generates a specific color based on the current iteration.
 * @details Uses trigonometric or polynomial functions to smoothly interpolate 
 * RGB values.
 * @param iter     The current iteration count for a pixel.
 * @param max_iter The maximum iterations allowed.
 * @return         The calculated color as an integer (0xRRGGBB).
 */
int	neon_cyberpunk_palette(int iter, int max_iter)
{
	double	tmp;
	double	glow;
	int		red;
	int		green;
	int		blue;

	tmp = (double)iter / max_iter;
	glow = sqrt(tmp);
	red = (int)(255 * glow * (0.5 + 0.5 * sin(15 * tmp)));
	green = (int)(255 * glow * (0.5 + 0.5 * sin(30 * tmp + 2.0)));
	blue = (int)(255 * glow * (0.5 + 0.5 * sin(10 * tmp + 4.0)));
	return ((red << 16) | (green << 8) | blue);
}

/**
 * @fn int phoenix_glow_palette(int iter, int max_iter)
 * @brief Generates a specific color based on the current iteration.
 * @details Uses trigonometric or polynomial functions to smoothly interpolate 
 * RGB values.
 * @param iter     The current iteration count for a pixel.
 * @param max_iter The maximum iterations allowed.
 * @return         The calculated color as an integer (0xRRGGBB).
 */
int	phoenix_glow_palette(int iter, int max_iter)
{
	double	tmp;
	int		red;
	int		green;
	int		blue;

	tmp = (double)iter / max_iter;
	red = (int)(255 * pow(sin(3.2 * tmp), 2));
	green = (int)(255 * pow(sin(3.0 * tmp - 0.5), 2));
	blue = (int)(255 * pow(sin(2.5 * tmp - 1.0), 2));
	if (red > 255)
		red = 255;
	if (green > 255)
		green = 255;
	if (blue > 255)
		blue = 255;
	if (red < 0)
		red = 0;
	if (green < 0)
		green = 0;
	if (blue < 0)
		blue = 0;
	return ((red << 16) | (green << 8) | blue);
}

/**
 * @fn int hsv_palette(int iter, int max_iter)
 * @brief Generates a specific color based on the current iteration.
 * @details Uses trigonometric or polynomial functions to smoothly interpolate 
 * RGB values.
 * @param iter     The current iteration count for a pixel.
 * @param max_iter The maximum iterations allowed.
 * @return         The calculated color as an integer (0xRRGGBB).
 */
int	hsv_palette(int iter, int max_iter)
{
	double	tmp;
	double	f;
	int		i;
	int		v;
	int		p;
	int		q;

	tmp = (double)iter / max_iter;
	v = (int)(255 * sqrt(tmp));
	i = (int)(tmp * 6);
	f = tmp * 6 - i;
	q = (int)(v * (1 - f));
	p = (int)(v * f);
	if (i % 6 == 0)
		return ((v << 16) | (p << 8));
	if (i % 6 == 1)
		return ((q << 16) | (v << 8));
	if (i % 6 == 2)
		return ((0 << 16) | (v << 8) | p);
	if (i % 6 == 3)
		return ((0 << 16) | (q << 8) | v);
	if (i % 6 == 4)
		return ((p << 16) | (0 << 8) | v);
	return ((v << 16) | (0 << 8) | q);
}
