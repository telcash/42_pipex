/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:01:55 by csalazar          #+#    #+#             */
/*   Updated: 2024/10/21 21:07:22 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_pipex_b(int fd1, int fd2, int argc, int first_com_index, char **argv,
		char **envp)
{
	int		end[2];
	pid_t	pid;
	int		i;
	int		fd;

	i = first_com_index;
	while (i < argc - 2)
	{
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
		{
			if (i == first_com_index)
				fd = fd1;
			ft_child_proc(fd, argv[i], end, envp);
		}
		waitpid(0, NULL, 0);
		fd = dup(end[0]);
		close(end[1]);
		i++;
	}
	close(fd);
	ft_parent_proc(fd2, argv[i], end, envp);
}

void	ft_set_fds(int *fd1, int *fd2, int *first_com_index, int argc,
		char **argv)
{
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc < 6)
		{
			ft_putstr_fd("Bad arguments\n", 2);
			exit(EXIT_FAILURE);
		}
		ft_here_doc(argv[2], fd1);
		*fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		*first_com_index = 3;
	}
	else
	{
		*fd1 = open(argv[1], O_RDONLY, 0777);
		*fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		*first_com_index = 2;
	}
	if (*fd1 == -1 || *fd2 == -1)
	{
		if (*fd1 >= 0)
			close(*fd1);
		if (*fd2 >= 0)
			close(*fd2);
		ft_perror();
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	fd1;
	int	fd2;
	int	first_com_index;

	if (argc >= 5)
	{
		ft_set_fds(&fd1, &fd2, &first_com_index, argc, argv);
		ft_pipex_b(fd1, fd2, argc, first_com_index, argv, envp);
	}
	else
		ft_putstr_fd("Bad arguments,\n", 2);
	return (0);
}
