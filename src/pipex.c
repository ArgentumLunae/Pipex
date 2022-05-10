/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/18 11:26:15 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/05/10 17:23:39 by mteerlin      ########   odam.nl         */
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

void	free_args(t_args *args)
{
	free_twod(args->paths);
	free_threed(args->cmds);
	free(args);
}

t_args	*parse_args(int argc, char **argv, char **env)
{
	char	**paths;
	t_args	*args;

	paths = get_paths(env);
	args = malloc(sizeof(t_args));
	if (!args)
	{
		perror("Allocation error.");
		exit(EXIT_FAILURE);
	}
	args->cmds = lst_cmds(argc, argv);
	args->paths = malloc(3 * sizeof(char *));
	args->paths[0] = cmd_path(paths, args->cmds[0]);
	args->paths[1] = cmd_path(paths, args->cmds[1]);
	args->paths[2] = NULL;
	args->fdio[0] = open(argv[1], O_RDONLY);
	if (args->fdio[0] < 0)
	{
		perror("Open file descriptor failure.");
		exit(EXIT_FAILURE);
	}
	if (!ft_strncmp(args->cmds[argc - 4][0], "apnd", (ft_strlen("apnd") + 1)))
	{
		args->fdio[1] = open(argv[argc - 1], \
			O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
		free_twod(args->cmds[argc - 4]);
		args->cmds[argc - 4] = NULL;
	}
	else
	{
		args->fdio[1] = open(argv[argc - 1], \
			O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	}
	ft_printf("parse_args:\t%s\n", args->cmds[0][0]);
	free_twod(paths);
	ft_printf("parse_args:\t%s\n", args->cmds[0][0]);
	return (args);
}

int	main(int argc, char **argv, char **env)
{
	t_args		*args;

	if (argc < 5 && argv)
	{
		perror("Incorrect number of arguments. (5 arguments required)");
		exit(EXIT_FAILURE);
	}
	args = parse_args(argc, argv, env);
	ft_printf("main:\t%s\n", args->cmds[0][0]);
	execcmd(args, env);
	//system("leaks pipex");
	return (0);
}
