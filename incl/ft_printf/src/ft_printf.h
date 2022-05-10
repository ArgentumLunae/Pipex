/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/15 11:48:49 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/03/24 15:47:36 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define CONVERSION_CHAR "cspdiuxX%"
# define FLAG_CHAR "-0 .*"
# include <stdarg.h>
# include <stddef.h>
# include "../../libft/libft.h"

typedef struct s_mods
{
	unsigned int	lallign;
	unsigned int	fillzero;
	int				precision;
	int				width;
	int				sign;
	char			*modstr;
}				t_mods;

int				ft_printf(const char *format, ...);
int				pf_parse(const char **format, t_mods *mods, va_list args);
int				pf_sign_dec(int nbr, t_mods *mods);
int				pf_usign_base(unsigned int nbr, unsigned int base, \
								t_mods *mods, const char format);
int				pf_string(char *str, t_mods *mods);
int				pf_character(int c, t_mods *mods);
int				pf_pointer(void *ptr, t_mods *mods);
int				pf_percentile(t_mods *mods);
size_t			det_size(int len, t_mods *mods);
int				build_precision(int len, t_mods *mods, char **arr);
int				prep_modstr(int size, t_mods *mods);
int				fill_modstr(int len, int size, char **arr, t_mods *mods);
#endif
