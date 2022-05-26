/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/18 11:26:15 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/05/26 15:42:53 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/pipex.h"
#include "../incl/ft_printf/src/ft_printf.h"

int	main(int argc, char **argv, char **env)
{
	if (argc < 5)
	{
		ft_printf("Usage: ./pipex filepath cmd ... cmd filepath.\n");
		exit(EXIT_FAILURE);
	}
	setup_exec(argc, argv, env);
	while (wait(NULL) == 0)
		;
	return (0);
}
