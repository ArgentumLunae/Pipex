/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/18 12:23:55 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/05/10 12:36:37 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define PATHDIR "/usr/bin/"

# include <stdbool.h>

typedef struct s_args
{
	char	**paths;
	char	***cmds;
	int		fdio[2];
}	t_args;

char	**get_paths(char **env);
void	free_twod(char **twod);
void	free_threed(char ***threed);

char	*cmd_path(char **paths, char **cmd);

void	execcmd(t_args *args, char **env);

#endif