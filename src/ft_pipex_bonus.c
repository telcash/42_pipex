/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:01:55 by csalazar          #+#    #+#             */
/*   Updated: 2024/10/20 22:27:37 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void    ft_pipex_b(int fd1, int fd2, int argc, char **argv, char **envp)
{
    int end[2];
    pid_t pid;
    int i;
    int fd;

    i = 2;
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
            if (i == 2)
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

int main(int argc, char **argv, char **envp)
{
    int fd1;
    int fd2;

    if (argc >= 5)
    {
        fd1 = open(argv[1], O_RDONLY, 0777);
		fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd1 == -1 || fd2 == -1)
        {
			if (fd1 >= 0)
				close (fd1);
			if (fd2 >= 0)
				close (fd2);
            perror("Error: ");
			return (1);
        }
        ft_pipex_b(fd1, fd2, argc, argv, envp);
    }
    else
		ft_putstr_fd("Bad arguments. Try: ./pipex infile cmd1 cmd2 outfile\n", 1);
	return (0);
}