/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   accesscmd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 11:41:46 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/05/10 16:35:52 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../hdr/pipex.h"
#include "../incl/ft_printf/src/ft_printf.h"
#include <unistd.h>

char	*cmd_path(char **paths, char **cmd)
{
	int		cnt;
	char	*cmdpath;

	cnt = 0;
	while (paths[cnt])
	{
		cmdpath = ft_strjoin(paths[cnt], cmd[0]);
		ft_printf("cmd_path: %s\n", cmdpath);
		if (!access(cmdpath, X_OK))
		{
			ft_printf("%s is accesable\n", cmdpath);
			return (cmdpath);
		}
		free(cmdpath);
		cnt++;
	}
	ft_printf("%s is not accessable\n", cmd[0]);
	return (NULL);
}
