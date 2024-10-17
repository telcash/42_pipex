/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:39:40 by csalazar          #+#    #+#             */
/*   Updated: 2024/10/15 09:30:30 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/include/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

void	ft_pipex(int fd1, int fd2, char **argv, char **envp);
void	ft_child_proc(int fd, char *cmd1, int *end, char **envp);
char	*ft_find_path(char *cmd, char **envp);
void	free_str_arr(char **str_arr);

#endif