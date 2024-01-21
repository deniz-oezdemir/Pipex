/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:27:31 by denizozd          #+#    #+#             */
/*   Updated: 2024/01/21 18:14:18 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
