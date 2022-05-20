/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   openio.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/15 14:14:14 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/05/15 16:49:50 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/pipex.h"
#include <fcntl.h>

int	open_infile(char *argv[])
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("fd failure.");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	open_outfile(int argc, char *argv[], bool app)
{
	int	fd;

	if (app == false)
		fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	else
		fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	if (fd < 0)
	{
		perror("fd failure.");
		exit(EXIT_FAILURE);
	}
	return (fd);
}
