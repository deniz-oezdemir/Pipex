/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:41:06 by denizozd          #+#    #+#             */
/*   Updated: 2024/01/26 14:52:25 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Execute the specified command with arguments and environment variables:
Splits the command string into an array of arguments,
retrieves the full path of the command,
and executes the command using execve. */
void	exec(char *av, char **ev)
{

	char	**cmd;
	char	*path;
	int		i;

	cmd = ft_split(av, ' ');
	path = get_path(cmd[0], ev);
	i = 0;
	if (path == 0)
	{
		while (cmd[i])
			free(cmd[i++]);
		free(cmd);
		err();
	}
	if (execve(path, cmd, ev) == -1)
	{
		free_split(cmd);
		free(path);
		err();
	}
}

/* Get the full path of the command by searching through the PATH variable:
Searches through the PATH variable to find the full path of
the command (where it is executed),
returns the full path (including the command) if found, or
NULL if the command is not in any of the specified paths. */
char	*get_path(char *cmd, char **ev)
{
	char	**all_paths;
	char	*path;
	char	*path_part;
	int		i;

	i = 0;
	while (ft_strnstr(ev[i], "PATH", 4) == 0)
		i++;
	all_paths = ft_split(ev[i] + 5, ':');
	i = 0;
	while (all_paths[i])
	{
		path_part = ft_strjoin(all_paths[i], "/");
		path = ft_strjoin(path_part, cmd);
		free(path_part);
		if (access(path, F_OK) == 0)
		{
			free_split(all_paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_split(all_paths);
	return (0);
}

/* Frees the memory allocated for an array of strings such as
the one created with ft_split. */
void	free_split(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

/* Displays an error on stderr message using perror and exit the program. */
void	err(void)
{
	perror("Error");
	exit(0);
}
