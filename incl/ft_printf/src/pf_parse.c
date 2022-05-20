/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_parse.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/15 12:27:19 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/05/15 14:19:33 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

static int	parse_width(const char **format, t_mods *mods, va_list args)
{
	int	arg;

	arg = 0;
	if (**format == '*')
	{
		arg = va_arg(args, int);
		if (arg < 0)
		{
			mods->lallign = 1;
			mods->fillzero = 0;
			mods->width = arg * -1;
		}
		else
			mods->width = arg;
	}
	else
	{
		mods->width = ft_atoi(*format);
		while (ft_isdigit(*(*format + 1)))
			(*format)++;
	}
	return (1);
}

static int	parse_precision(const char **format, t_mods *mods, va_list args)
{
	if (*(*format + 1) == '*')
	{
		(*format)++;
		mods->precision = va_arg(args, int);
	}
	else if (ft_isdigit(*(*format + 1)))
	{
		(*format)++;
		mods->precision = ft_atoi(*format);
		while (ft_isdigit(*(*format + 1)))
			(*format)++;
	}
	else
		mods->precision = 0;
	return (1);
}

static int	parse_flags(const char **format, t_mods *mods, va_list args)
{
	if (**format == '-')
		mods->lallign = 1;
	else if (**format == '0' && mods->lallign <= 0)
		mods->fillzero = 1;
	else if ((**format != '0' && ft_isdigit(**format)) || **format == '*')
		parse_width(format, mods, args);
	else if (**format == '.')
		parse_precision(format, mods, args);
	if (mods->lallign > 0)
		mods->fillzero = 0;
	return (1);
}

static int	parse_conversion(const char **format, t_mods *mods, va_list args)
{
	if (**format == 'd' || **format == 'i')
		return (pf_sign_dec(va_arg(args, int), mods));
	else if (**format == 'c')
		return (pf_character(va_arg(args, int), mods));
	else if (**format == 's')
		return (pf_string(va_arg(args, char *), mods));
	else if (**format == 'p')
		return (pf_pointer(va_arg(args, void *), mods));
	else if (**format == 'u')
		return (pf_usign_base(va_arg(args, unsigned int), 10, mods, **format));
	else if (**format == 'x' || **format == 'X')
		return (pf_usign_base(va_arg(args, unsigned int), 16, mods, **format));
	else if (**format == '%')
		return (pf_percentile(mods));
	return (-1);
}

int	pf_parse(const char **format, t_mods *mods, va_list args)
{
	while (ft_strchr(FLAG_CHAR, **format) || ft_isdigit(**format))
	{
		parse_flags(format, mods, args);
		(*format)++;
	}
	if (ft_strchr(CONVERSION_CHAR, **format))
		return (parse_conversion(format, mods, args));
	return (-1);
}
