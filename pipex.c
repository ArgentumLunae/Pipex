/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/06 12:15:50 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/05/10 17:23:53 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hdr/pipex.h"
#include <stdio.h>
#include <stdlib.h>

t_args	*init_args(int argc, char **argv, char **env)
{
	char	**paths;
	t_args	*args;

	paths = get_paths(env);
}

int	main(int argc, char **argv, char **env)
{
	t_args	*args;

	if (argc != 5)
	{
		perror("incorrect number of arguments.\n");
		exit(EXIT_FAILURE);
	}
	args = init_args(argc, argv, env);
}
