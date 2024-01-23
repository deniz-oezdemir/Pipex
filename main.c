/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:27:31 by denizozd          #+#    #+#             */
/*   Updated: 2024/01/23 18:50:21 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* The main function checks if the correct number of arguments is provided,
sets up a pipe, forks a child process to execute the first command,
and the parent process executes the second command. */
int	main(int ac, char **av, char **ev)
{
	int		fd[2];
	pid_t	pid;

	if (ac != 5)
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
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
