/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:40:56 by denizozd          #+#    #+#             */
/*   Updated: 2024/01/21 10:03:39 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent(char **av, int **ev, int fd)
{
	int	fileout;

	fileout = open(av[3], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
		err();
	dup2(fd[0], 0);
	dup2(fileout, 1);
	close(fd[1]);
	exec(av[3], ev);
}

void	child(char **av, int **ev, int fd)
{
	int	filein;

	filein = open(av[1], O_RDONLY, 0777);
	if (filein == -1)
		err();
	dup2(filein, 0); //0 for STDIN_FILENO
	dup2(fd[1], 1); //1 for STDOUT_FILENO
	close(fd[0]);
	exec(av[2], ev);
}	
		
/*
- env: contains the environment variables to pass onto execve; can include
information such as the user's home directory, the path to executable files,
and other configuration settings
*/
int	main(int ac, char **av, char **ev)
{
	int		fd[2];
	pid_t	pid;

	if (ac != 5)
		err();
	else
	{
		if (pipe(fd) == -1)
			err();
		pid = fork();
		if (pid == -1)
			err();
		if (pid == 0)
			child(av, ev, fd);
		waitpid(pid, NULL, 0);
		parent(av, ev, fd);
	}	
	return (0);		
}
