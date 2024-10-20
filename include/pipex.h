/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:39:40 by csalazar          #+#    #+#             */
/*   Updated: 2024/10/20 16:57:39 by csalazar         ###   ########.fr       */
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
void	ft_child_proc(int fd, char *cmd, int *end, char **envp);
void    ft_parent_proc(int fd, char *cmd, int *end, char **envp);
char	*ft_find_path(char *cmd, char **envp);
void	free_str_arr(char **str_arr);
void	ft_exec_cmd(char *cmd, char **envp);
char	**ft_split_mod(char const *s);
void    ft_pipex_b(int fd1, int fd2, int argc, char **argv, char **envp);

#endif