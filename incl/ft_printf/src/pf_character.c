/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_character.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/20 11:18:18 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/03/02 15:57:24 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

int	pf_character(int c, t_mods *mods)
{
	int	ret;

	if (mods->width > 1)
	{
		mods->modstr = malloc((mods->width - 1) * sizeof(char));
		if (mods->modstr == NULL)
			return (-1);
		ft_memset(mods->modstr, ' ', (mods->width - 1));
		mods->modstr[mods->width - 1] = '\0';
	}
	else
		mods->modstr = ft_calloc(1, sizeof(char));
	if (mods->lallign > 0)
	{
		ft_putchar_fd(c, 1);
		ft_putstr_fd(mods->modstr, 1);
	}
	else
	{
		ft_putstr_fd(mods->modstr, 1);
		ft_putchar_fd(c, 1);
	}
	ret = ft_strlen(mods->modstr);
	ft_bzero(mods->modstr, mods->width);
	return (ret + 1);
}
