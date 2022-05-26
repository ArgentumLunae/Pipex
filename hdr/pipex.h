/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/18 12:23:55 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/05/26 15:15:37 by mteerlin      ########   odam.nl         */
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

bool	check_heredoc(char *argv);
void	cleanup(int fdio[2]);
void	next_pipe(int p1[2], int p2[2]);

int		open_infile(char *argv[]);
int		open_outfile(int argc, char *argv[]);

void	setup_exec(int argc, char *argv[], char *env[]);

#endif