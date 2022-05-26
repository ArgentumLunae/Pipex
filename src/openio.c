/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   openio.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/15 14:14:14 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/05/26 18:07:12 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/pipex.h"
#include <fcntl.h>

int	open_infile(char *argv[])
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		perror(argv[1]);
	return (fd);
}

int	open_outfile(int argc, char *argv[])
{
	int	fd;

	fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		perror(argv[argc - 1]);
	return (fd);
}
