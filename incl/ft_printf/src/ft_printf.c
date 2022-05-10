/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/15 11:47:48 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/03/10 16:10:20 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

int	start_convert(const char **format, va_list args)
{
	t_mods	mods;
	int		ret;

	(*format)++;
	ft_bzero(&mods, sizeof(t_mods));
	mods.precision = -1;
	ret = pf_parse(format, &mods, args);
	ft_putstr_fd(mods.modstr, 1);
	free(mods.modstr);
	mods.modstr = NULL;
	(*format)++;
	return (ret);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		ret;
	int		cnt;
	char	*wrstart;

	va_start(args, format);
	ret = 0;
	cnt = 0;
	wrstart = (char *)format;
	while (*format != '\0')
	{
		if (*format == '%')
		{
			write(1, wrstart, cnt);
			cnt = 0;
			ret += start_convert(&format, args);
			wrstart = (char *)format;
			continue ;
		}
		cnt++;
		ret++;
		format++;
	}
	write(1, wrstart, cnt);
	return (ret);
}
