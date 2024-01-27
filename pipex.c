/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:40:56 by denizozd          #+#    #+#             */
/*   Updated: 2024/01/27 14:54:49 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Executes the first command in the pipex program:
Opens the input file (0777 grants read, write, and execute permissions to the
owner, group, and others),
duplicates/redirects standard input (0 for STDIN_FILENO) to the file,
duplicates/redirects standard output (1 for STDOUT_FILENO) to the
writing end of the pipe,
closes the reading end of the pipe as it's not needed in this process,
and executes the specified command. */
void	child(char **av, char **ev, int *fd)
{
	int	file1;

	file1 = open(av[1], O_RDONLY, 0777);
	if (file1 == -1)
		err();
	dup2(file1, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	exec(av[2], ev);
}

/* Executes the second command in the pipex program:
Opens the output file with write-only mode, creates the file if it
does not exist, truncates the file to zero length if it exists,
redirects standard input to the reading end of the pipe,
redirects standard output to the opened output file,
closes the writing end of the pipe as it's not needed in this process,
and executes the specified command. */
void	parent(char **av, char **ev, int *fd)
{
	int	file2;

	file2 = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file2 == -1)
		err();
	dup2(fd[0], 0);
	dup2(file2, 1);
	close(fd[1]);
	exec(av[3], ev);
}
