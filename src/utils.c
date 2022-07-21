/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/15 14:15:33 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/07/21 14:28:56 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/pipex.h"
#include "../incl/libft/libft.h"
#include <unistd.h>

void	free_twod(char **twod)
{
	int	cnt;

	cnt = 0;
	while (twod[cnt] != NULL)
	{
		free(twod[cnt]);
		cnt++;
	}
	free(twod);
}

bool	check_heredoc(char *argv)
{
	bool	hd;

	hd = false;
	if (!ft_strncmp(argv, "here_doc", 9))
		hd = true;
	return (hd);
}

void	cleanup(int fdio[2])
{
	if (fdio != NULL)
	{
		close(fdio[0]);
		close(fdio[1]);
	}
}

void	next_pipe(int p1[2], int p2[2])
{
	p1[0] = p2[0];
	p1[1] = p2[1];
	if (pipe(p2) < 0)
		perror("pipe failure");
}
