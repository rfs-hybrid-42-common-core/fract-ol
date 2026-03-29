/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palettes2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:38:48 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/29 14:04:23 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

/**
 * @fn int autumn_palette(int iter, int max_iter)
 * @brief Generates a specific color based on the current iteration.
 * @details Uses trigonometric or polynomial functions to smoothly interpolate 
 * RGB values.
 * @param iter     The current iteration count for a pixel.
 * @param max_iter The maximum iterations allowed.
 * @return         The calculated color as an integer (0xRRGGBB).
 */
int	autumn_palette(int iter, int max_iter)
{
	double	tmp;
	int		red;
	int		green;
	int		blue;

	tmp = (double)iter / max_iter;
	red = (int)(255 * sqrt(tmp));
	green = (int)(255 * tmp * tmp);
	blue = (int)(255 * sqrt(tmp) * (1.0 - tmp));
	return ((red << 16) | (green << 8) | blue);
}

/**
 * @fn int autumn_frost_palette(int iter, int max_iter)
 * @brief Generates a specific color based on the current iteration.
 * @details Uses trigonometric or polynomial functions to smoothly interpolate 
 * RGB values.
 * @param iter     The current iteration count for a pixel.
 * @param max_iter The maximum iterations allowed.
 * @return         The calculated color as an integer (0xRRGGBB).
 */
int	autumn_frost_palette(int iter, int max_iter)
{
	double	tmp;
	int		red;
	int		green;
	int		blue;

	tmp = (double)iter / max_iter;
	red = (int)(255 * sqrt(tmp));
	red = (int)((0.8 * red) + (0.2 * (255 * (0.5 + 0.5 * sin(15 * tmp)))));
	green = (int)(255 * tmp * tmp);
	green = (int)((0.7 * green) + (0.3 * (255 * (0.5 + 0.5
						* sin(15 * tmp + 2)))));
	blue = (int)(255 * tmp * tmp * tmp * tmp);
	blue = (int)((0.5 * blue) + (0.5 * (255 * (0.5 + 0.5
						* sin(15 * tmp + 4)))));
	return ((red << 16) | (green << 8) | blue);
}

/**
 * @fn int firebird_psychedelic_palette(int iter, int max_iter)
 * @brief Generates a specific color based on the current iteration.
 * @details Uses trigonometric or polynomial functions to smoothly interpolate 
 * RGB values.
 * @param iter     The current iteration count for a pixel.
 * @param max_iter The maximum iterations allowed.
 * @return         The calculated color as an integer (0xRRGGBB).
 */
int	firebird_psychedelic_palette(int iter, int max_iter)
{
	double	tmp;
	int		red;
	int		green;
	int		blue;

	tmp = (double)iter / max_iter;
	red = (int)(255 * (0.6 + 0.4 * sin(60.0 * tmp)));
	green = (int)(255 * (0.5 + 0.5 * sin(60.0 * tmp - 0.8)));
	blue = (int)(255 * (0.5 + 0.5 * sin(60.0 * tmp - 3.14)));
	return ((red << 16) | (green << 8) | blue);
}

/**
 * @fn int winter_sunrise_palette(int iter, int max_iter)
 * @brief Generates a specific color based on the current iteration.
 * @details Uses trigonometric or polynomial functions to smoothly interpolate 
 * RGB values.
 * @param iter     The current iteration count for a pixel.
 * @param max_iter The maximum iterations allowed.
 * @return         The calculated color as an integer (0xRRGGBB).
 */
int	winter_sunrise_palette(int iter, int max_iter)
{
	double	tmp;
	int		red;
	int		green;
	int		blue;

	tmp = (double)iter / max_iter;
	red = (int)(255 * (1 - tmp) * tmp * tmp * 255);
	red = (int)((0.7 * red)
			+ (0.3 * (100 * (0.5 + 0.5 * sin(6.2831 * tmp + 4)))));
	green = (int)(100 * (1 - tmp) * (1 - tmp) * tmp * 255);
	green = (int)((0.8 * green)
			+ (0.2 * (150 * (0.5 + 0.5 * sin(6.2831 * tmp + 2)))));
	blue = (int)(50 * (1 - tmp) * (1 - tmp) * (1 - tmp) * 255);
	blue = (int)((0.7 * blue)
			+ (0.3 * (150 * (0.5 + 0.5 * sin(6.2831 * tmp + 2)))));
	return ((red << 16) | (green << 8) | blue);
}

/**
 * @fn int funky_galaxy_palette(int iter, int max_iter)
 * @brief Generates a specific color based on the current iteration.
 * @details Uses trigonometric or polynomial functions to smoothly interpolate 
 * RGB values.
 * @param iter     The current iteration count for a pixel.
 * @param max_iter The maximum iterations allowed.
 * @return         The calculated color as an integer (0xRRGGBB).
 */
int	funky_galaxy_palette(int iter, int max_iter)
{
	double	tmp;
	int		red;
	int		green;
	int		blue;

	tmp = (double)iter / max_iter;
	red = (int)(100 * (1 - tmp) * tmp * 255);
	red = (int)((0.8 * red) + (0.2 * (255 * (0.5 + 0.5 * sin(10 * tmp)))));
	green = (int)(50 * (1 - tmp) * (1 - tmp) * tmp * 255);
	green = (int)((0.8 * green) + (0.2 * (255 * (0.5 + 0.5 * sin(10 * tmp)))));
	blue = (int)(200 * (1 - tmp) * (1 - tmp) * (1 - tmp) * 255);
	blue = (int)((0.8 * blue) + (0.2 * (255 * (0.5 + 0.5 * sin(10 * tmp)))));
	return ((red << 16) | (green << 8) | blue);
}
