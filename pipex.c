/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:40:56 by denizozd          #+#    #+#             */
/*   Updated: 2024/01/21 18:14:47 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent(char **av, char **ev, int *fd)
{
	int	fileout;

	fileout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
		err();
	dup2(fd[0], 0);
	dup2(fileout, 1);
	close(fd[1]);
	exec(av[3], ev);
}

void	child(char **av, char **ev, int *fd)
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
