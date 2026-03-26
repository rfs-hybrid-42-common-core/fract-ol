/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:25:57 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/26 04:16:00 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

/**
 * @fn int exit_program(t_display *disp)
 * @brief Cleanly exits the application.
 * @details Destroys the MLX image, window, and display pointers, frees memory, 
 * and exits.
 * @param disp Pointer to the display structure.
 * @return     EXIT_SUCCESS (Required by MLX hook prototype, though it calls 
 * exit() internally).
 */
int	exit_program(t_display *disp)
{
	mlx_destroy_image(disp->mlx, disp->data.img);
	mlx_destroy_window(disp->mlx, disp->win);
	mlx_destroy_display(disp->mlx);
	free(disp->mlx);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

/**
 * @fn void print_invalid_input(void)
 * @brief Displays correct usage instructions to the user.
 * @details Prints the available fractals and their required command-line 
 * arguments, then exits.
 */
void	print_invalid_input(void)
{
	ft_putendl_fd("*******************************************", STDERR_FILENO);
	ft_putendl_fd("******** Invalid input parameters! ********", STDERR_FILENO);
	ft_putendl_fd("*******************************************", STDERR_FILENO);
	ft_putendl_fd("\nAvailable fractals:", STDERR_FILENO);
	ft_putendl_fd("\tMandelbrot | Julia | Tricorn | Burning Ship | Phoenix",
		STDERR_FILENO);
	ft_putendl_fd("Run one of the following to execute the fractal program:",
		STDERR_FILENO);
	ft_putendl_fd("\tMandelbrot: ./fractol_bonus mandelbrot", STDERR_FILENO);
	ft_putendl_fd("\tJulia: ./fractol_bonus julia <real> <imag>",
		STDERR_FILENO);
	ft_putendl_fd("\tTricorn: ./fractol_bonus tricorn", STDERR_FILENO);
	ft_putendl_fd("\tBurning Ship: ./fractol_bonus 'burning ship'",
		STDERR_FILENO);
	ft_putendl_fd("\tPhoenix: ./fractol_bonus phoenix <real> <imag> <delta>",
		STDERR_FILENO);
	ft_putendl_fd("\tPhoenix Variant: ./fractol_bonus 'phoenix variant' <real> "
		"<imag> <delta>", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

/**
 * @fn static double get_fractional(const char *nptr)
 * @brief Parses the fractional part of a double.
 * @details Calculates the decimal values and ensures no trailing garbage 
 * characters or illegal spaces exist after the number.
 * @param nptr Pointer to the string right after the decimal point.
 * @return     The parsed fractional value.
 */
static double	get_fractional(const char *nptr)
{
	double	frac;
	double	div;

	frac = 0.0;
	div = 10.0;
	while (ft_isdigit(*nptr))
	{
		frac += (*nptr++ - '0') / div;
		div *= 10.0;
	}
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr != '\0')
		print_invalid_input();
	return (frac);
}

/**
 * @fn double ft_atod(const char *nptr)
 * @brief Converts an ASCII string to a double-precision floating-point number.
 * @details Parses the integer and fractional parts of the string. It strictly 
 * enforces formatting, aborting the program and displaying usage instructions 
 * if it encounters invalid characters, multiple signs, or misplaced spaces.
 * @param nptr The string to parse.
 * @return     The parsed double value.
 */
double	ft_atod(const char *nptr)
{
	double	res;
	int		sign;

	res = 0.0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		if (*nptr++ == '-')
			sign = -1;
	if (!ft_isdigit(*nptr) && !(*nptr == '.' && ft_isdigit(*(nptr + 1))))
		print_invalid_input();
	while (ft_isdigit(*nptr))
		res = res * 10.0 + (*nptr++ - '0');
	if (*nptr == '.')
		nptr++;
	return ((res + get_fractional(nptr)) * sign);
}
