/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dirs.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 13:46:47 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/05/10 15:40:36 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft/libft.h"
#include "../incl/ft_printf/src/ft_printf.h"
#include <stdlib.h>

void	free_twod(char **twod)
{
	int	cnt;

	cnt = 0;
	while (twod[cnt] != NULL)
	{
		free(twod[cnt]);
		cnt++;
	}
	free(twod);
}

char	**get_dirs(char **env)
{
	int		cnt;
	char	*tmp;
	char	**dirs;

	cnt = 0;
	while (env[cnt] != NULL)
	{
		if (ft_strnstr(env[cnt], "PATH=", 5))
			break ;
		cnt++;
	}
	tmp = ft_strdup(&(env[cnt][5]));
	dirs = ft_split(tmp, ':');
	free(tmp);
	cnt = 0;
	while (dirs[cnt])
	{
		tmp = ft_strjoin(dirs[cnt], "/");
		free(dirs[cnt]);
		dirs[cnt] = tmp;
		cnt++;
	}
	return (dirs);
}
