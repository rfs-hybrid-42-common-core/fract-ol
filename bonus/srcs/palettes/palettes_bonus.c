/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palettes_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:38:52 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/26 03:11:00 by maaugust         ###   ########.fr       */
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
 * @fn int lava_lamp_palette(int iter, int max_iter)
 * @brief Generates a specific color based on the current iteration.
 * @details Uses trigonometric or polynomial functions to smoothly interpolate 
 * RGB values.
 * @param iter     The current iteration count for a pixel.
 * @param max_iter The maximum iterations allowed.
 * @return         The calculated color as an integer (0xRRGGBB).
 */
int	lava_lamp_palette(int iter, int max_iter)
{
	double	tmp;
	int		red;
	int		green;
	int		blue;

	tmp = (double)iter / max_iter;
	red = (int)(255 * (0.5 + 0.5 * cos(3.0 * 3.1415 * tmp)));
	green = (int)(255 * (0.5 + 0.5 * sin(6.2831 * tmp + 1.0)));
	blue = (int)(255 * (0.5 + 0.5 * sin(3.0 * 3.1415 * tmp)));
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
	int		i;
	double	f;
	int		q;
	int		p;

	tmp = (double)iter / max_iter;
	i = (int)(tmp * 6);
	f = tmp * 6 - i;
	q = (int)(255 * (1 - f));
	p = (int)(255 * f);
	if (i % 6 == 0)
		return ((255 << 16) | (p << 8));
	if (i % 6 == 1)
		return ((q << 16) | (255 << 8));
	if (i % 6 == 2)
		return ((0 << 16) | (255 << 8) | p);
	if (i % 6 == 3)
		return ((0 << 16) | (q << 8) | 255);
	if (i % 6 == 4)
		return ((p << 16) | (0 << 8) | 255);
	return ((255 << 16) | (0 << 8) | q);
}

/**
 * @fn int electric_carnival_palette(int iter, int max_iter)
 * @brief Generates a specific color based on the current iteration.
 * @details Uses trigonometric or polynomial functions to smoothly interpolate 
 * RGB values.
 * @param iter     The current iteration count for a pixel.
 * @param max_iter The maximum iterations allowed.
 * @return         The calculated color as an integer (0xRRGGBB).
 */
int	electric_carnival_palette(int iter, int max_iter)
{
	double	tmp;
	int		red;
	int		green;
	int		blue;

	tmp = (double)iter / max_iter;
	red = (int)(255 * (0.5 + 0.5 * sin(8 * tmp + 0)));
	red = (int)((0.8 * red) + (0.2 * (255 * (0.5 + 0.5 * sin(10 * tmp)))));
	green = (int)(255 * (0.5 + 0.5 * sin(8 * tmp + 2)));
	green = (int)((0.7 * green)
			+ (0.3 * (255 * (0.5 + 0.5 * sin(10 * tmp)))));
	blue = (int)(255 * (0.5 + 0.5 * sin(8 * tmp + 4)));
	blue = (int)((0.6 * blue) + (0.4 * (255 * (0.5 + 0.5 * sin(10 * tmp)))));
	return ((red << 16) | (green << 8) | blue);
}
