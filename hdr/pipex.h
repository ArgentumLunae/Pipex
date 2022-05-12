/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/18 12:23:55 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/05/12 17:09:08 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define PATHDIR "/usr/bin/"

# include <stdbool.h>

char	**get_dirs(char **env);
void	free_twod(char **twod);
void	free_threed(char ***threed);

char	*cmd_path(char **paths, char *cmd);

void	setup_exec(char **dirs, int argc, char *argv[], char *env[]);

#endif