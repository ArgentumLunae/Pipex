/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/18 12:23:55 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/07/01 14:03:56 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define PATHDIR "/usr/bin/"

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

void	free_twod(char **twod);
char	**get_dirs(char **env);
char	*cmd_path(char **paths, char **cmd);

bool	check_heredoc(char *argv);
void	cleanup(int fdio[2]);
void	next_pipe(int p1[2], int p2[2]);

int		open_infile(char *infile);
int		open_outfile(char *outfile);

void	setup_exec(int argc, char *argv[]);

#endif