/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_signed_dec.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/29 13:32:49 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/03/02 13:39:47 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

int	pf_sign_dec(int nbr, t_mods *mods)
{
	int		templen;
	int		totlen;
	char	*temp;

	temp = ft_itoa_base((long long int)nbr, 10);
	if (temp == NULL)
		return (-1);
	if (mods->precision >= 0)
		mods->fillzero = 0;
	if (nbr < 0)
		mods->sign = 1;
	templen = ft_strlen(temp);
	if (mods->precision == 0 && nbr == 0 && build_precision(0, mods, &temp) < 0)
		return (-1);
	else if (mods->precision >= templen)
	{
		if (build_precision(templen, mods, &temp) < 0)
			return (-1);
	}
	templen = ft_strlen(temp);
	totlen = det_size(templen, mods);
	if (prep_modstr(totlen, mods))
		return (fill_modstr(templen, totlen, &temp, mods));
	return (-1);
}
