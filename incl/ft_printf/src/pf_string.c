/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_string.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/29 14:19:14 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/03/02 10:24:10 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static char	*string_precision(int len, char *str, t_mods *mods)
{
	char	*arr;

	if (mods->precision < len && mods->precision >= 0)
	{
		arr = (char *)malloc((mods->precision + 1) * sizeof(char));
		if (!arr)
			return (NULL);
		ft_strlcpy(arr, str, (mods->precision + 1));
	}
	else
	{
		arr = ft_strdup(str);
		if (!arr)
			return (NULL);
	}
	return (arr);
}

int	pf_string(char *str, t_mods *mods)
{
	int		len;
	int		size;
	char	*arr;

	if (str == NULL)
	{
		if ((mods->precision < 0 && mods->precision > 6))
			str = ft_strdup("");
		else
			str = ft_strdup("(null)");
	}
	if (mods->precision >= 0)
		mods->fillzero = 0;
	arr = string_precision(ft_strlen(str), str, mods);
	if (!arr)
		return (-1);
	len = ft_strlen(arr);
	size = len;
	if (mods->width > len)
		size = mods->width;
	if (prep_modstr(size, mods) == -1)
		return (-1);
	return (fill_modstr((int)ft_strlen(arr), size, &arr, mods));
}
