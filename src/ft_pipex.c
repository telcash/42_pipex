/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:04:30 by csalazar          #+#    #+#             */
/*   Updated: 2024/10/18 10:57:55 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_child_proc(int fd, char *cmd1, int *end, char **envp)
{
	char	**cmd;
	char	*path;

	dup2(fd, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	close(fd);
	//ft_putstr_fd(cmd1,2);
	cmd = ft_split_mod(cmd1);
	path = ft_find_path(cmd[0], envp);
	if (!path)
	{
		ft_putstr_fd("not found\n", 2);
		free_str_arr(cmd);
		exit(EXIT_FAILURE);
	}
/* 	ft_putstr_fd(cmd[0],2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd(cmd[1],2);
	ft_putchar_fd('\n', 2); */
	if (execve(path, cmd, envp) == -1)
	{
		perror("Error5");
		exit(EXIT_FAILURE);
	}
}

void	ft_parent_proc(int fd, char *cmd2, int *end, char **envp)
{
	char	**cmd;
	char	*path;

	dup2(fd, STDOUT_FILENO);
	dup2(end[0], STDIN_FILENO);
	close(end[1]);
	close(fd);
	cmd = ft_split_mod(cmd2);
	/* ft_putstr_fd(cmd2,2);
	ft_putchar_fd('\n', 2); */
	cmd = ft_split_mod(cmd2);
	path = ft_find_path(cmd[0], envp);
	if (!path)
	{
		ft_putstr_fd("not found\n", 2);
		free_str_arr(cmd);
		exit(EXIT_FAILURE);
	}
/* 	ft_putstr_fd(cmd[0],2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd(cmd[1],2);
	ft_putchar_fd('\n', 2); */
	if (execve(path, cmd, envp) == -1)
	{
		perror("Error3");
		exit(EXIT_FAILURE);
	}
}

void	ft_pipex(int fd1, int fd2, char **argv, char **envp)
{
	int		end[2];
	pid_t	parent;

	pipe(end);
	parent = fork();
	if (parent == -1)
		return (perror("Error1"));
	if (!parent)
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
	else
		ft_putstr_fd("Bad arguments. Try: ./pipex infile cmd1 cmd2 outfile\n", 1);
	return (0);
}
