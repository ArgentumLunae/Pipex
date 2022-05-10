/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execcmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 17:18:37 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/05/10 19:06:23 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/pipex.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../incl/ft_printf/src/ft_printf.h"
#include <stdio.h>

void	execcmd(t_args *args, char **env)
{
	int	p[2];
	char buff[500];

	if (pipe(p) < 0)
	{
		perror("pipe failure.\n");
		exit(EXIT_FAILURE);
	}
	if (fork() == 0)
	{
		dup2(p[1], STDOUT_FILENO);
		dup2(args->fdio[0], STDIN_FILENO);
		if (execve(args->paths[0], args->cmds[0], env))
		{
			perror("execution is fucked");
			exit(EXIT_FAILURE);
		}
	}
	else if (fork() == 0)
	{
		dup2(p[0], STDIN_FILENO);
		dup2(args->fdio[1], STDOUT_FILENO);
		ft_bzero(buff, 500);
		read(STDIN_FILENO, buff, 499);
		ft_printf("%s\n", buff);
		ft_printf("execcmd: %s\n", args->paths[0]);
		ft_printf("execcmd: %s %s %s\n", args->cmds[0][0], args->cmds[0][1], args->cmds[0][2]);
		if (execve(args->paths[0], args->cmds[0], env))
		{
			perror("execution is fucked");
			exit(EXIT_FAILURE);
		}
	}
	else
		while (wait(NULL) == 0)
			;
	ft_printf("I'm done waiting on this shit\n");
}
