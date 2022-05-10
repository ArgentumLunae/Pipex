/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/08 17:13:19 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/03/02 13:25:49 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

size_t	det_size(int len, t_mods *mods)
{
	if (mods->width > len)
		len = mods->width;
	if (mods->precision > len)
		len = mods->precision;
	return (len);
}

int	build_precision(int len, t_mods *mods, char **arr)
{
	char	*temp;
	int		preclen;

	preclen = mods->precision + mods->sign;
	temp = malloc((preclen + 1) * sizeof(char));
	if (!temp)
		return (-1);
	ft_memset(temp, '0', preclen);
	temp[preclen] = '\0';
	while ((preclen - mods->sign) > 0)
	{
		if ((len - mods->sign) > 0)
			temp[preclen - 1] = (*arr)[len - 1];
		else
			temp[preclen - 1] = '0';
		len--;
		preclen--;
	}
	if (mods->sign == 1)
		temp[0] = (*arr)[0];
	free(*arr);
	(*arr) = temp;
	temp = NULL;
	return (ft_strlen(*arr));
}

int	prep_modstr(int size, t_mods *mods)
{
	mods->modstr = malloc((size + 1) * sizeof(char));
	if (mods->modstr == NULL)
		return (-1);
	if (mods->fillzero > 0)
		ft_memset(mods->modstr, '0', size);
	else
		ft_memset(mods->modstr, ' ', size);
	mods->modstr[size] = '\0';
	return (1);
}

int	fill_modstr(int len, int size, char **arr, t_mods *mods)
{
	if (mods->lallign == 1 || size == len)
	{
		ft_memcpy(mods->modstr, *arr, len);
	}
	else
	{
		size--;
		while (len > mods->sign)
		{
			mods->modstr[size] = (*arr)[len - 1];
			size--;
			len--;
		}
		while (mods->fillzero == 1 && size >= mods->sign)
		{
			mods->modstr[size] = '0';
			size--;
		}
		if (mods->sign == 1)
			mods->modstr[size] = (*arr)[len - 1];
	}
	free(*arr);
	*arr = NULL;
	return (ft_strlen(mods->modstr));
}
