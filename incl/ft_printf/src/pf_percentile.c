/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_percentile.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 15:58:07 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/03/02 16:08:06 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static int	fillwidth(t_mods *mods)
{
	mods->modstr = malloc((mods->width - 1) * sizeof(char));
	if (mods->modstr == NULL)
		return (-1);
	if (mods->fillzero == 1)
		ft_memset(mods->modstr, '0', (mods->width - 1));
	else
		ft_memset(mods->modstr, ' ', (mods->width - 1));
	mods->modstr[mods->width - 1] = '\0';
	return (1);
}

int	pf_percentile(t_mods *mods)
{
	int	ret;

	if (mods->width > 1)
	{
		if (fillwidth(mods) == -1)
			return (-1);
	}
	else
		mods->modstr = ft_calloc(1, sizeof(char));
	if (mods->lallign > 0)
	{
		ft_putchar_fd('%', 1);
		ft_putstr_fd(mods->modstr, 1);
	}
	else
	{
		ft_putstr_fd(mods->modstr, 1);
		ft_putchar_fd('%', 1);
	}
	ret = ft_strlen(mods->modstr);
	ft_bzero(mods->modstr, mods->width);
	return (ret + 1);
}
