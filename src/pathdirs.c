/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pathdirs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/26 15:10:06 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/07/29 15:12:27 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

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
	free(tmp);
	if (dirs == NULL)
		return (NULL);
	cnt = 0;
	slash_dirs(&dirs);
	return (dirs);
}

char	*cmd_path(char **paths, char **cmd)
{
	int		cnt;
	char	*cmdpath;

	cnt = 0;
	if (paths == NULL || cmd == NULL)
		return (NULL);
	while (paths[cnt])
	{
		cmdpath = ft_strjoin(paths[cnt], cmd[0]);
		if (!access(cmdpath, X_OK))
			return (cmdpath);
		free(cmdpath);
		cnt++;
	}
	return (NULL);
}
