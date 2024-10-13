/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:39:40 by csalazar          #+#    #+#             */
/*   Updated: 2024/10/13 19:33:04 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <fcntl.h>
# include "../libft/include/libft.h"

void    ft_pipex(int fd1, int fd2, char **argv, char **envp);
char    **ft_find_path(char *cmd, char **envp);
void    free_str_arr(char **str_arr);

#endif