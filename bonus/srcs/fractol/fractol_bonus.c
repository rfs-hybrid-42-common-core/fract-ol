/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:19:45 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/27 14:39:17 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

/**
 * @fn static bool is_valid_name(char *input, const char *target)
 * @brief Compares input against a target fractal name, ignoring surrounding 
 * spaces.
 * @details Skips leading/trailing whitespace and performs a case-insensitive 
 * match.
 * @param input  The string to validate (from argv).
 * @param target The macro defined fractal name to match against.
 * @return       true if the string matches perfectly, false otherwise.
 */
static bool	is_valid_name(char *input, const char *target)
{
	int	i;

	while (ft_isspace(*input))
		input++;
	i = -1;
	while (target[++i])
		if (ft_toupper(input[i]) != target[i])
			return (false);
	while (ft_isspace(input[i]))
		i++;
	return (input[i] == '\0');
}

/**
 * @fn static void parse_phoenix_delta(t_fractal *frac, char *delta)
 * @brief Parses and clamps the delta parameter for Phoenix fractals.
 * @details Converts the string input to a double using ft_atod and enforces 
 * bounds between DELTA_MIN and DELTA_MAX to prevent mathematical overflow.
 * @param frac  Pointer to the main fractal structure.
 * @param delta The string containing the delta value.
 */
static void	parse_phoenix_delta(t_fractal *frac, char *delta)
{
	frac->delta = ft_atod(delta);
	if (frac->delta < DELTA_MIN)
		frac->delta = DELTA_MIN;
	else if (frac->delta > DELTA_MAX)
		frac->delta = DELTA_MAX;
}

/**
 * @fn static bool is_julia_phoenix(t_fractal *frac, int argc, char **argv)
 * @brief Validates arguments specifically for Julia and Phoenix fractals.
 * @details Checks argument counts, parses inputs, and sets the correct type.
 * @param frac Pointer to the main fractal structure.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return     true if it is a valid Julia or Phoenix setup, false otherwise.
 */
static bool	is_julia_phoenix(t_fractal *frac, int argc, char **argv)
{
	if (argc == 4 && is_valid_name(argv[1], JULIA_NAME))
	{
		frac->disp.name = JULIA_NAME;
		frac->type = JULIA_TYPE;
	}
	else if (argc == 5 && is_valid_name(argv[1], PHOENIX_NAME))
	{
		frac->disp.name = PHOENIX_NAME;
		frac->type = PHOENIX_TYPE;
	}
	else if (argc == 5 && is_valid_name(argv[1], PHOENIX_VARIANT_NAME))
	{
		frac->disp.name = PHOENIX_VARIANT_NAME;
		frac->type = PHOENIX_VARIANT_TYPE;
	}
	else
		return (false);
	frac->c.re = ft_atod(argv[2]);
	frac->c.im = ft_atod(argv[3]);
	if (argc == 5)
		parse_phoenix_delta(frac, argv[4]);
	return (true);
}

/**
 * @fn static void validate_inputs(t_fractal *frac, int argc, char **argv)
 * @brief Validates all command-line inputs.
 * @details Routes to specific validators or assigns simple fractal names. 
 * Exits on invalid input.
 * @param frac Pointer to the main fractal structure.
 * @param argc Argument count.
 * @param argv Argument vector.
 */
static void	validate_inputs(t_fractal *frac, int argc, char **argv)
{
	if (is_julia_phoenix(frac, argc, argv))
		return ;
	else if (argc == 2)
	{
		if (is_valid_name(argv[1], MANDELBROT_NAME))
		{
			frac->disp.name = MANDELBROT_NAME;
			frac->type = MANDELBROT_TYPE;
		}
		else if (is_valid_name(argv[1], BURNING_SHIP_NAME))
		{
			frac->disp.name = BURNING_SHIP_NAME;
			frac->type = BURNING_SHIP_TYPE;
		}
		else if (is_valid_name(argv[1], TRICORN_NAME))
		{
			frac->disp.name = TRICORN_NAME;
			frac->type = TRICORN_TYPE;
		}
		else
			print_invalid_input();
	}
	else
		print_invalid_input();
}

/**
 * @fn int main(int argc, char **argv)
 * @brief Entry point for the fract'ol program.
 * @details Validates inputs, initializes structures, renders the first frame, 
 * and starts the MLX loop.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return     EXIT_SUCCESS upon clean termination.
 */
int	main(int argc, char **argv)
{
	t_fractal	frac;

	validate_inputs(&frac, argc, argv);
	init(&frac);
	render(&frac);
	mlx_key_hook(frac.disp.win, handle_key_event, &frac);
	mlx_hook(frac.disp.win, DestroyNotify, NoEventMask, exit_program, &frac);
	mlx_mouse_hook(frac.disp.win, handle_mouse_event, &frac);
	mlx_loop(frac.disp.mlx);
	return (EXIT_SUCCESS);
}
