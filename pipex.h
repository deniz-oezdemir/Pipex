/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:40:45 by denizozd          #+#    #+#             */
/*   Updated: 2024/01/29 11:09:32 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <fcntl.h>    /* open */
# include <stdio.h>    /* perror */
# include <sys/wait.h> /* waitpid */
# include <unistd.h>   /* pipe, fork, close, access, dup2, execve */

void	child(char **av, char **ev, int *fd);
void	parent(char **av, char **ev, int *fd);
void	exec(char *av, char **ev);
char	*get_path(char *cmd, char **ev);
void	free_split(char **strs);
void	err(int nbr);

#endif
