/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/18 11:26:15 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/05/20 14:17:40 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/pipex.h"
#include "../incl/ft_printf/src/ft_printf.h"
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
	if (dirs == NULL)
		return (NULL);
	free(tmp);
	cnt = 0;
	slash_dirs(&dirs);
	return (dirs);
}

int	main(int argc, char **argv, char **env)
{
	char	**dirs;

	if (argc < 5 && argv)
	{
		ft_printf("Usage: ./pipex filepath cmd cmd filepath.\n");
		exit(EXIT_FAILURE);
	}
	dirs = get_dirs(env);
	setup_exec(dirs, argc, argv, env);
	while (wait(NULL) == 0)
		;
	return (0);
}
