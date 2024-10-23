/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:01:55 by csalazar          #+#    #+#             */
/*   Updated: 2024/10/22 13:30:32 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void ft_parent_proc_b(int fin, int fout, char *com, char **envp)
{
	int		end[2];
	
	if (pipe(end) == -1)
		ft_perror();
	dup2(fin, end[0]);
	close(fin);
	ft_parent_proc(fout, com, end, envp);
}

int	ft_child_proc_b(int fin, char *com, char **envp)
{
	int		end[2];
	pid_t	pid;
	int		next_fin;

	if (pipe(end) == -1)
		ft_perror();
	pid = fork();
	if (pid == -1)
		ft_perror();
	if (pid == 0)
		ft_child_proc(fin, com, end, envp);
	waitpid(0, NULL, 0);
	next_fin = dup(end[0]);
	close(end[1]);
	close(fin);
	return (next_fin);
}

void	ft_set_fds(int *fd1, int *fd2, int argc, char **argv)
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
	}
	else
	{
		*fd1 = open(argv[1], O_RDONLY, 0777);
		*fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
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
	int i;
	int fin;

	if (argc >= 5)
	{
		ft_set_fds(&fd1, &fd2, argc, argv);
		if (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc >= 6)
			first_com_index = 3;
		else
			first_com_index = 2;
		i = first_com_index;
		fin = fd1;
		while (i < argc - 2)
		{
			fin = ft_child_proc_b(fin, argv[i], envp);
			i++;
		}
		ft_parent_proc_b(fin, fd2, argv[i], envp);
	}
	else
		ft_putstr_fd("Bad arguments,\n", 2);
	return (0);
}
