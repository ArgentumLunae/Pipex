/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execcmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 17:18:37 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/07/21 14:28:28 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/pipex.h"
#include "../incl/libft/libft.h"
#include <unistd.h>

void	child(char *argv, int pin[2], int pout[2])
{
	extern char	**environ;
	char		**dirs;
	char		**cmd;
	char		*path;

	dirs = get_dirs(environ);
	cmd = ft_split(argv, ' ');
	path = cmd_path(dirs, cmd);
	if (path == NULL)
	{
		if (cmd == NULL)
			write(2, "(null)", 6);
		else
			write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, ": command not found\n", 20);
		exit(EXIT_FAILURE);
	}
	if (dup2(pin[0], STDIN_FILENO) < 0 || dup2(pout[1], STDOUT_FILENO) < 0)
		perror(NULL);
	if (execve(path, cmd, environ))
		perror(NULL);
}

void	fork_first(char *infile, char *argv, int pout[2])
{
	pid_t		spork;
	int			fd;

	spork = fork();
	if (spork == 0)
	{
		fd = open_infile(infile);
		if (fd >= 0)
			child(argv, (int [2]){fd, -1}, pout);
		else
			exit(EXIT_FAILURE);
	}
	else if (spork < 0)
		perror(NULL);
	else
		close(pout[1]);
}

void	fork_middle(char *argv, int pin[2], int pout[2])
{
	pid_t	spork;

	spork = fork();
	if (spork == 0)
		child(argv, pin, pout);
	else if (spork < 0)
		perror(NULL);
	else
		cleanup((int [2]){pin[0], pout[1]});
}

void	fork_last(char *outfile, char *argv, int pin[2])
{
	pid_t	spork;
	int		fd;

	spork = fork();
	if (spork == 0)
	{
		fd = open_outfile(outfile);
		if (fd >= 0)
			child(argv, pin, (int [2]){-1, fd});
		else
			exit(EXIT_FAILURE);
	}
	else if (spork < 0)
		perror(NULL);
	else
		close(pin[0]);
}

void	setup_exec(int argc, char *argv[])
{
	int		p1[2];
	int		p2[2];
	int		cnt;

	if (pipe(p2))
		perror("pipe error");
	fork_first(argv[1], argv[2], p2);
	cnt = 3;
	while (cnt < (argc - (2)))
	{
		next_pipe(p1, p2);
		fork_middle(argv[cnt], p1, p2);
		cnt++;
	}
	fork_last(argv[argc - 1], argv[cnt], p2);
}
