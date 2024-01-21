/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:41:06 by denizozd          #+#    #+#             */
/*   Updated: 2024/01/21 17:17:19 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *av, char **ev)
{
	char	**cmd;
	char	*path;
	int	i;

	cmd = ft_split(av, ' '); //add split, check for double frees
	path = get_path(cmd[0], ev);
	i = 0;
	if (path == 0)
	{
		while (cmd[i])
			free(cmd[i++]); //indexing: check mem leaks
		free(cmd);
		err();
	}
	if (execve(path, cmd, ev) == -1)
		err();
}

char	*get_path(char	*cmd, char **ev)
{
	char	**all_paths;
	char	*path;
	char	*path_part;
	int	i;

	i = 0;
	while(ft_strnstr(ev[i], "PATH", 4) == 0) //libft
		i++;
	all_paths = ft_split(ev[i] + 5, ':'); //+5 to jump PATH\n
	i = 0;
	while (all_paths[i])
	{
		path_part = ft_strjoin(all_paths[i], "/"); //libft
		path = ft_strjoin(path_part, cmd);
		free(path_part);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = 0;
	while (all_paths[i])
		free(all_paths[i++]);
	free(all_paths);
	return (0);
}

void	err(void)
{
	perror("Error");
	exit(0);
}
