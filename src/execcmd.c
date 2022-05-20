/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execcmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 17:18:37 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/05/20 14:40:52 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/pipex.h"
#include "../incl/ft_printf/src/ft_printf.h"
#include <unistd.h>

char	*cmd_path(char **paths, char *cmd)
{
	int		cnt;
	char	*cmdpath;

	cnt = 0;
	if (paths == NULL)
		return (NULL);
	while (paths[cnt])
	{
		cmdpath = ft_strjoin(paths[cnt], cmd);
		if (!access(cmdpath, X_OK))
			return (cmdpath);
		free(cmdpath);
		cnt++;
	}
	return (NULL);
}

bool	exec_cmd(char **dirs, char *argv, char *env[], int fdio[2])
{
	char	*path;
	char	**cmd;
	pid_t	spork;

	cmd = ft_split(argv, ' ');
	path = cmd_path(dirs, cmd[0]);
	if (path == NULL)
		ft_printf("%s: command not found\n", cmd[0]);
	spork = fork();
	if (spork < 0)
		return (false);
	if (spork == 0)
	{
		if (dup2(fdio[0], STDIN_FILENO) < 0)
			return (false);
		if (dup2(fdio[1], STDOUT_FILENO) < 0)
			return (false);
		execve(path, cmd, env);
	}
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

	if (pipe(p2))
		perror("pipe error");
	fd = open_infile(argv);
	cnt = 2;
	if (!exec_cmd(dirs, argv[cnt], env, (int [2]){fd, p2[1]}))
		perror("fork error");
	close(fd);
	cnt++;
	app = check_append(argc, argv);
	while (cnt < (argc - (2 + app)))
	{
		next_pipe(p1, p2);
		if (!exec_cmd(dirs, argv[cnt], env, (int [2]){p1[0], p2[1]}))
			perror("fork error");
		cnt++;
	}
	fd = open_outfile(argc, argv, app);
	if (!exec_cmd(dirs, argv[cnt], env, (int []){p2[0], fd}))
		perror("fork error");
}
