/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/18 11:26:15 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/07/21 14:28:45 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../hdr/pipex.h"

int	main(int argc, char **argv)
{
	if (argc < 5)
	{
		write(1, "Usage: ./pipex filepath cmd ... cmd filepath.\n", 46);
		exit(EXIT_FAILURE);
	}
	setup_exec(argc, argv);
	while (wait(NULL) == 0)
		;
	return (0);
}
