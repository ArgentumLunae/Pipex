/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execcmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 17:18:37 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/05/26 18:06:57 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/pipex.h"
#include "../incl/ft_printf/src/ft_printf.h"
#include <unistd.h>

char	*cmd_path(char **paths, char **cmd)
{
	int		cnt;
	char	*cmdpath;

	cnt = 0;
	if (paths == NULL || cmd == NULL)
		exit(EXIT_FAILURE);
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

void	exec_cmd(char *argv, char *env[], int fdio[2])
{
	pid_t	spork;
	char	**dirs;
	char	**cmd;
	char	*path;

	spork = fork();
	if (spork == 0)
	{
		dirs = get_dirs(env);
		cmd = ft_split(argv, ' ');
		path = cmd_path(dirs, cmd);
		if (path == NULL)
		{
			ft_printf("%s: command not found\n", cmd[0]);
			exit(EXIT_FAILURE);
		}
		if (dup2(fdio[0], STDIN_FILENO) < 0 || dup2(fdio[1], STDOUT_FILENO) < 0)
			perror("dup2 error");
		if (execve(path, cmd, env))
			perror(NULL);
	}
	else if (spork < 0)
		perror("fork error");
	else
		cleanup(fdio);
}

void	setup_exec(int argc, char *argv[], char *env[])
{
	int		p1[2];
	int		p2[2];
	int		fd;
	int		cnt;

	if (pipe(p2))
		perror("pipe error");
	fd = open_infile(argv);
	if (fd >= 0)
		exec_cmd(argv[2], env, (int [2]){fd, p2[1]});
	else
		close(p2[1]);
	cnt = 3;
	while (cnt < (argc - (2)))
	{
		next_pipe(p1, p2);
		exec_cmd(argv[cnt], env, (int [2]){p1[0], p2[1]});
		cnt++;
	}
	fd = open_outfile(argc, argv);
	if (fd >= 0)
		exec_cmd(argv[cnt], env, (int [2]){p2[0], fd});
	else
		close(p2[0]);
}
