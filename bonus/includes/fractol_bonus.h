/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:19:25 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/29 20:33:00 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_BONUS_H
# define FRACTOL_BONUS_H

/* ========================================================================== */
/* INCLUDES                                                                   */
/* ========================================================================== */

/* --------------------------- External Libraries --------------------------- */
# include "libft.h"
# include "mlx.h"

/* --------------------------- Internal Libraries --------------------------- */
# include <math.h>
# include <stdbool.h>
# include <X11/X.h>
# include <X11/keysym.h>

/* ========================================================================== */
/* MACROS                                                                     */
/* ========================================================================== */

/* -------------------------- Screen Resolutions ---------------------------- */

/**
 * @def WIDTH_800
 * @brief Default window width (800 pixels).
 */
# define WIDTH_800				800

/**
 * @def HEIGHT_600
 * @brief Default window height (600 pixels).
 */
# define HEIGHT_600				600

/**
 * @def WIDTH_1024
 * @brief Medium window width (1024 pixels).
 */
# define WIDTH_1024				1024

/**
 * @def HEIGHT_768
 * @brief Medium window height (768 pixels).
 */
# define HEIGHT_768				768

/**
 * @def WIDTH_1280
 * @brief Large window width (1280 pixels).
 */
# define WIDTH_1280				1280

/**
 * @def HEIGHT_720
 * @brief Large window height (720 pixels).
 */
# define HEIGHT_720				720

/**
 * @def WIDTH_1680
 * @brief Widescreen window width (1680 pixels).
 */
# define WIDTH_1680				1680

/**
 * @def HEIGHT_1050
 * @brief Widescreen window height (1050 pixels).
 */
# define HEIGHT_1050			1050 

/* ----------------------------- Complex Plane ------------------------------ */

/**
 * @def XMIN
 * @brief Minimum real axis bound for the complex plane view.
 */
# define XMIN					-2.0

/**
 * @def XMAX
 * @brief Maximum real axis bound for the complex plane view.
 */
# define XMAX					2.0

/**
 * @def YMIN
 * @brief Minimum imaginary axis bound for the complex plane view.
 */
# define YMIN					-2.0

/**
 * @def YMAX
 * @brief Maximum imaginary axis bound for the complex plane view.
 */
# define YMAX					2.0

/**
 * @def OFF_X_INIT
 * @brief Initial horizontal offset for the view.
 */
# define OFF_X_INIT				0.0

/**
 * @def OFF_Y_INIT
 * @brief Initial vertical offset for the view.
 */
# define OFF_Y_INIT				0.0

/**
 * @def FRAC_LIMIT
 * @brief Escape radius squared (typically 4.0 for Mandelbrot/Julia).
 */
# define FRAC_LIMIT				4.0

/* ------------------------------- Palettes --------------------------------- */

/**
 * @def PALETTE_INIT
 * @brief Default starting palette index.
 */
# define PALETTE_INIT			0

/**
 * @def PALETTE_TOTAL
 * @brief Total number of color palettes available.
 */
# define PALETTE_TOTAL			10

/* -------------------------- Navigation & Zoom ----------------------------- */

/**
 * @def ZOOM_SCALE
 * @brief Multiplier used when zooming in or out.
 */
# define ZOOM_SCALE				0.9

/**
 * @def ZOOM_MIN
 * @brief Maximum zoom-in limit to prevent precision loss.
 */
# define ZOOM_MIN				1.0e-9

/**
 * @def ZOOM_MAX
 * @brief Maximum zoom-out limit.
 */
# define ZOOM_MAX				5.0

/**
 * @def ZOOM_INIT
 * @brief Initial zoom level.
 */
# define ZOOM_INIT				1.0

/**
 * @def PADDING_SCALE
 * @brief Base translation distance for arrow key panning.
 */
# define PADDING_SCALE			0.25

/* ------------------------------- Shading ---------------------------------- */

/**
 * @def SHADE_SCALE
 * @brief Step amount for increasing/decreasing color shading.
 */
# define SHADE_SCALE			0.1

/**
 * @def SHADE_MIN
 * @brief Minimum shading value (darkest).
 */
# define SHADE_MIN				0.0

/**
 * @def SHADE_MAX
 * @brief Maximum shading value (brightest/original color).
 */
# define SHADE_MAX				1.0

/**
 * @def SHADE_INIT
 * @brief Initial shading multiplier.
 */
# define SHADE_INIT				1.0

/* ------------------------------ Iterations -------------------------------- */

/**
 * @def ITER_SCALE
 * @brief Step amount to increase/decrease fractal depth.
 */
# define ITER_SCALE				25

/**
 * @def ITER_MIN
 * @brief Minimum allowable rendering iterations.
 */
# define ITER_MIN				25

/**
 * @def ITER_MAX
 * @brief Maximum allowable rendering iterations.
 */
# define ITER_MAX				1000

/**
 * @def ITER_INIT
 * @brief Default starting iterations.
 */
# define ITER_INIT				100

/* --------------------------- Phoenix Variables ---------------------------- */

/**
 * @def DELTA_SCALE
 * @brief Step amount to modify the Phoenix delta value.
 */
# define DELTA_SCALE			0.02

/**
 * @def DELTA_MIN
 * @brief Minimum allowable Phoenix delta.
 */
# define DELTA_MIN				-1.0

/**
 * @def DELTA_MAX
 * @brief Maximum allowable Phoenix delta.
 */
# define DELTA_MAX				1.0

/* ----------------------------- Mouse Buttons ------------------------------ */

/**
 * @def MOUSE_LEFT
 * @brief X11 left mouse button code.
 */
# define MOUSE_LEFT      		1

/**
 * @def MOUSE_RIGHT
 * @brief X11 right mouse button code.
 */
# define MOUSE_RIGHT     		2

/**
 * @def MOUSE_MIDDLE
 * @brief X11 middle mouse button code.
 */
# define MOUSE_MIDDLE    		3

/**
 * @def MOUSE_SCROLL_UP
 * @brief X11 scroll up button code.
 */
# define MOUSE_SCROLL_UP 		4

/**
 * @def MOUSE_SCROLL_DOWN
 * @brief X11 scroll down button code.
 */
# define MOUSE_SCROLL_DOWN		5

/* ----------------------------- Fractal Names ------------------------------ */

/**
 *  @def MANDELBROT_NAME
 *  @brief Command line identifier for Mandelbrot.
 */
# define MANDELBROT_NAME		"MANDELBROT"

/**
 *  @def JULIA_NAME
 *  @brief Command line identifier for Julia.
 */
# define JULIA_NAME				"JULIA"

/**
 *  @def BURNING_SHIP_NAME
 *  @brief Command line identifier for Burning Ship.
 */
# define BURNING_SHIP_NAME		"BURNING SHIP"

/**
 *  @def TRICORN_NAME
 *  @brief Command line identifier for Tricorn.
 */
# define TRICORN_NAME			"TRICORN"

/**
 *  @def PHOENIX_NAME
 *  @brief Command line identifier for Phoenix.
 */
# define PHOENIX_NAME			"PHOENIX"

/**
 *  @def PHOENIX_VARIANT_NAME
 *  @brief Command line identifier for Phoenix Variant.
 */
# define PHOENIX_VARIANT_NAME	"PHOENIX VARIANT"

/* ========================================================================== */
/* TYPEDEFS                                                                   */
/* ========================================================================== */

/**
 * @typedef t_palette_func
 * @brief Function pointer type for color palette generators.
 * @param iter     The current iteration depth of the pixel.
 * @param max_iter The maximum iteration depth allowed.
 * @return         An integer representing the generated RGB color.
 */
typedef int	(*t_palette_func)(int iter, int max_iter);

/* ========================================================================== */
/* DATA STRUCTURES                                                            */
/* ========================================================================== */

/**
 * @enum e_fractal_type
 * @brief Identifies the mathematical algorithm used for rendering.
 * @details Replaces string comparisons to quickly route the rendering loop 
 * to the correct mathematical formula.
 * @var MANDELBROT_TYPE      Standard Mandelbrot set.
 * @var JULIA_TYPE           Standard Julia set.
 * @var BURNING_SHIP_TYPE    Burning Ship fractal (absolute value variation).
 * @var TRICORN_TYPE         Tricorn fractal (conjugated variation).
 * @var PHOENIX_TYPE         Standard Phoenix set.
 * @var PHOENIX_VARIANT_TYPE Visual variant of the Phoenix set.
 */
typedef enum e_fractal_type
{
	MANDELBROT_TYPE,
	JULIA_TYPE,
	BURNING_SHIP_TYPE,
	TRICORN_TYPE,
	PHOENIX_TYPE,
	PHOENIX_VARIANT_TYPE
}	t_fractal_type;

/**
 * @struct s_data
 * @brief Holds MiniLibX image buffer data.
 * @details Allows for fast memory-level writing of pixels instead of using 
 * the slow mlx_pixel_put function.
 * @var img      Pointer to the image object.
 * @var addr     Memory address of the start of the image buffer.
 * @var bpp      Bits per pixel.
 * @var line_len Length of a single image line in bytes.
 * @var endian   Endianness of the local architecture.
 */
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_data;

/**
 * @struct s_complex
 * @brief Represents a complex number.
 * @var re Real part of the complex number.
 * @var im Imaginary part of the complex number.
 */
typedef struct s_complex
{
	double	re;
	double	im;
}	t_complex;

/**
 * @struct s_display
 * @brief Manages the MiniLibX window and rendering context.
 * @var mlx    Pointer to the MLX instance.
 * @var win    Pointer to the MLX window instance.
 * @var data   Image data buffer structure.
 * @var name   The name of the window (usually the fractal name).
 * @var width  Width of the window in pixels.
 * @var height Height of the window in pixels.
 */
typedef struct s_display
{
	void			*mlx;
	void			*win;
	t_data			data;
	char			*name;
	int				width;
	int				height;
}	t_display;

/**
 * @struct s_fractal
 * @brief Central state structure for the fract'ol application.
 * @details Contains everything needed to compute, navigate, and color the sets.
 * @var disp        The display context and image buffers.
 * @var type        The active enum identifying the fractal to draw.
 * @var color       The current pixel's computed color.
 * @var shade       The shading multiplier (0.0 to 1.0) applied to the color.
 * @var iter        The current iteration count of the rendering loop.
 * @var max_iter    The maximum depth/iterations allowed before assuming a 
 * point is in the set.
 * @var x           Current X coordinate of the pixel being drawn.
 * @var y           Current Y coordinate of the pixel being drawn.
 * @var off_x       Horizontal offset for panning the view.
 * @var off_y       Vertical offset for panning the view.
 * @var zoom        Current zoom multiplier.
 * @var z           The complex number Z used in the mathematical formulas.
 * @var c           The complex number C representing the current pixel's 
 * coordinate.
 * @var delta       The extra parameter used specifically for Phoenix sets.
 * @var delta_init  The initial delta value cached to restore the fractal on 
 * reset.
 * @var is_gray     Boolean flag toggling grayscale shading.
 * @var palette_idx The index of the currently active color palette.
 * @var palette     Array of function pointers to the available palettes.
 * @var n_palettes  The total number of loaded palettes.
 */
typedef struct s_fractal
{
	t_display		disp;
	t_fractal_type	type;
	int				color;
	double			shade;
	int				iter;
	int				max_iter;
	int				x;
	int				y;
	double			off_x;
	double			off_y;
	double			zoom;
	t_complex		z;
	t_complex		c;
	double			delta;
	double			delta_init;
	bool			is_gray;
	int				palette_idx;
	t_palette_func	palette[PALETTE_TOTAL];
	int				n_palettes;
}	t_fractal;

/* ========================================================================== */
/* FUNCTIONS                                                                  */
/* ========================================================================== */

/* ----------------------- Initialization & Rendering ----------------------- */
void	init(t_fractal *frac);
void	render(t_fractal *frac);

/* ----------------------------- Event Handling ----------------------------- */
int		handle_key_event(int keysym, t_fractal *frac);
int		handle_mouse_event(int button, int x, int y, t_fractal *frac);

/* ------------------------------- Algorithms ------------------------------- */
void	mandelbrot(t_fractal *frac);
void	julia(t_fractal *frac);
void	tricorn(t_fractal *frac);
void	burning_ship(t_fractal *frac);
void	phoenix(t_fractal *frac);
void	phoenix_variant(t_fractal *frac);

/* ------------------------------- Utilities -------------------------------- */
int		exit_program(t_display *disp);
void	print_invalid_input(void);
double	ft_atod(const char *nptr);

/* -------------------------------- Palettes -------------------------------- */
int		blue_orange_palette(int iter, int max_iter);
int		inferno_palette(int iter, int max_iter);
int		neon_cyberpunk_palette(int iter, int max_iter);
int		phoenix_glow_palette(int iter, int max_iter);
int		hsv_palette(int iter, int max_iter);
int		autumn_palette(int iter, int max_iter);
int		autumn_frost_palette(int iter, int max_iter);
int		firebird_psychedelic_palette(int iter, int max_iter);
int		winter_sunrise_palette(int iter, int max_iter);
int		funky_galaxy_palette(int iter, int max_iter);

#endif
