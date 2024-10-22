/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:04:30 by csalazar          #+#    #+#             */
/*   Updated: 2024/10/22 08:43:02 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_pipex(int fd1, int fd2, char **argv, char **envp)
{
	int		end[2];
	pid_t	pid;

	if (pipe(end) == -1)
	{
		perror("Error: ");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error: ");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		ft_child_proc(fd1, argv[2], end, envp);
	waitpid(0, NULL, 0);
	ft_parent_proc(fd2, argv[3], end, envp);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd1;
	int	fd2;

	if (argc == 5)
	{
		fd1 = open(argv[1], O_RDONLY, 0777);
		fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd1 == -1 || fd2 == -1)
		{
			if (fd1 >= 0)
				close (fd1);
			if (fd2 >= 0)
				close (fd2);
			perror("Error: ");
			return (1);
		}
		ft_pipex(fd1, fd2, argv, envp);
	}
	ft_putstr_fd("Bad arguments.\n", 2);
	ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
	return (0);
}
