/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:27:31 by denizozd          #+#    #+#             */
/*   Updated: 2024/01/29 11:08:13 by denizozd         ###   ########.fr       */
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
		err(1);
	else if (ft_strncmp(av[1], "/dev/urandom", 12) == 0)
		err(0);
	else
	{
		if (pipe(fd) == -1)
			err(0);
		pid = fork();
		if (pid == -1)
			err(0);
		if (pid == 0)
			child(av, ev, fd);
		waitpid(pid, NULL, 0);
		parent(av, ev, fd);
	}
	return (0);
}
