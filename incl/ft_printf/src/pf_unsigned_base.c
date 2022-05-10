/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_unsigned_base.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/15 16:30:09 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/03/02 10:03:52 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static int	pf_precision_len(int nbr, int len, char **temp, t_mods *mods)
{
	if (((mods->precision == 0 && nbr == 0) || mods->precision > len))
		return (build_precision(len, mods, temp));
	return (len);
}

int	pf_usign_base(unsigned int nbr, unsigned int base, \
							t_mods *mods, const char format)
{
	int		preslen;
	int		totlen;
	char	*temp;

	temp = ft_itoa_base(nbr, base);
	if (temp == NULL)
		return (-1);
	if (mods->precision >= 0)
		mods->fillzero = 0;
	preslen = pf_precision_len(nbr, ft_strlen(temp), &temp, mods);
	if (preslen < 0)
		return (-1);
	totlen = det_size(preslen, mods);
	if (prep_modstr(totlen, mods) < 0)
		return (-1);
	if (fill_modstr(preslen, totlen, &temp, mods) < 0)
		return (-1);
	preslen = 0;
	while (format == 'X' && mods->modstr[preslen] != '\0')
	{
		mods->modstr[preslen] = ft_toupper(mods->modstr[preslen]);
		preslen++;
	}
	return (totlen);
}
