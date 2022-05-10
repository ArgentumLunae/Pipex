/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_pointers.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/29 13:36:37 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/03/02 11:23:58 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <stdlib.h>

int	pf_pointer(void *ptr, t_mods *mods)
{
	int		templen;
	int		totlen;
	char	*temp;
	char	*temp2;

	if (ptr == NULL && mods->precision == 0)
		temp = ft_strdup("");
	else if (ptr == NULL)
		temp = ft_strdup("0");
	else
		temp = ft_itoa_base((long long int)ptr, 16);
	temp2 = ft_strjoin("0x", temp);
	free(temp);
	temp = temp2;
	if (temp == NULL)
		return (-1);
	templen = ft_strlen(temp);
	totlen = det_size(templen, mods);
	if (prep_modstr(totlen, mods) < 0)
		return (-1);
	return (fill_modstr(templen, totlen, &temp, mods));
}
