/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pathdirs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/26 15:10:06 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/05/26 15:10:50 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft/libft.h"
#include <stdlib.h>

void	slash_dirs(char ***dirs)
{
	int		cnt;
	char	*tmp;

	cnt = 0;
	while ((*dirs)[cnt])
	{
		tmp = ft_strjoin((*dirs)[cnt], "/");
		free((*dirs)[cnt]);
		(*dirs)[cnt] = tmp;
		cnt++;
	}
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
	if (env[cnt] == NULL)
		return (NULL);
	tmp = ft_strdup(&(env[cnt][5]));
	dirs = ft_split(tmp, ':');
	if (dirs == NULL)
		return (NULL);
	free(tmp);
	cnt = 0;
	slash_dirs(&dirs);
	return (dirs);
}
