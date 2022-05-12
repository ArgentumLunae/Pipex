/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/18 11:26:15 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/05/12 17:48:15 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../incl/libft/libft.h"
#include "../incl/ft_printf/src/ft_printf.h"
#include "../hdr/pipex.h"
#include <stdio.h>

char	***lst_cmds(int argc, char *argv[])
{
	int		cnt;
	char	***ret;

	cnt = 0;
	ret = malloc((argc - 3) * sizeof(char **));
	if (!ret)
		return (NULL);
	while (cnt < argc - 3)
	{
		ret[cnt] = ft_split(argv[cnt + 2], ' ');
		if (!ret[cnt])
			return (NULL);
		cnt++;
	}
	ret[cnt] = NULL;
	return (ret);
}

int	main(int argc, char **argv, char **env)
{
	char	**dirs;

	close(19);
	if (argc < 5 && argv)
	{
		perror("Incorrect number of arguments. (5 arguments required)");
		exit(EXIT_FAILURE);
	}
	dirs = get_dirs(env);
	setup_exec(dirs, argc, argv, env);
	while (wait(NULL) == 0)
		;
	return (0);
}
