/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/18 12:23:55 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/05/15 16:54:54 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define PATHDIR "/usr/bin/"

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

void	free_twod(char **twod);

bool	check_append(int argc, char *argv[]);
void	cleanup(char *path, char **cmd, int fdio[2]);
void	next_pipe(int p1[2], int p2[2]);

int		open_infile(char *argv[]);
int		open_outfile(int argc, char *argv[], bool app);

void	setup_exec(char **dirs, int argc, char *argv[], char *env[]);

#endif