/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execcmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 17:18:37 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/05/12 19:46:55 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/pipex.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../incl/ft_printf/src/ft_printf.h"
#include <stdio.h>

void	cleanup(char *path, char **cmd, int fdio[2])
{
	close(fdio[0]);
	close(fdio[1]);
	free(path);
	free_twod(cmd);
}

void	next_pipe(int p1[2], int p2[2])
{
	close(p1[0]);
	close(p1[1]);
	p1[0] = p2[0];
	p1[1] = p2 [1];
	if (pipe(p2) < 0)
		perror("pipe failure");
}

bool	exec_cmd(char **dirs, char *argv, char *env[], int fdio[2])
{
	char	*path;
	char	**cmd;
	pid_t	spork;

	cmd = ft_split(argv, ' ');
	path = cmd_path(dirs, cmd[0]);
	spork = fork();
	if (spork == 0)
	{
		if (dup2(fdio[0], STDIN_FILENO) < 0)
			return (false);
		if (dup2(fdio[1], STDOUT_FILENO) < 0)
			return (false);
		execve(path, cmd, env);
	}
	else if (spork < 0)
		return (false);
	else
		cleanup(path, cmd, fdio);
	return (true);
}

void	setup_exec(char **dirs, int argc, char *argv[], char *env[])
{
	int		p1[2];
	int		p2[2];
	int		fd;
	int		cnt;
	bool	app;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		perror("fd failure.");
	if (pipe(p2) < 0)
		perror("pipe failure.\n");
	cnt = 2;
	if (!exec_cmd(dirs, argv[cnt], env, (int [2]){fd, p2[1]}))
		perror("fork failure");
	close(fd);
	cnt++;
	app = false;
	if (!ft_strncmp(argv[argc - 2], "-a", 3))
		app = true;
	while (cnt < (argc - (2 + app)))
	{
		next_pipe(p1, p2);
		if (!exec_cmd(dirs, argv[cnt], env, (int [2]){p1[0], p2[1]}))
			perror("fork failure");
		cnt++;
	}
	if (app == false)
		fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	else
		fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	if (fd < 0)
		perror("fd failure");
	if (!exec_cmd(dirs, argv[cnt], env, (int []){p2[0], fd}))
		perror("fork failure");
}
