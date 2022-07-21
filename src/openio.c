/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   openio.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/15 14:14:14 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/07/01 13:45:36 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/pipex.h"
#include <fcntl.h>

int	open_infile(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
		perror(infile);
	return (fd);
}

int	open_outfile(char *outfile)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		perror(outfile);
	return (fd);
}
