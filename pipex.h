/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:40:45 by denizozd          #+#    #+#             */
/*   Updated: 2024/01/21 16:43:39 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"

/* check which libraries are needed for whihc functions */
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

void	child(char **av, char **ev, int *fd);
void	parent(char **av, char **ev, int *fd);
void	exec(char *av, char **ev);
char	*get_path(char	*cmd, char **ev);
void	err(void);

#endif