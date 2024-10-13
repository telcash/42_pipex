/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:04:30 by csalazar          #+#    #+#             */
/*   Updated: 2024/10/13 19:41:10 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void ft_child_proc(int fd, char *cmd1, int *end, char **envp)
{
    char **cmd;
    char *path;

    dup2(fd, STDIN_FILENO);
    dup2(end[1], STDOUT_FILENO);
    close(end[0]);
    close(fd);
    cmd = ft_split(cmd1, ' ');
    path = ft_find_path(cmd[0], envp);
    if (!path)
    {
        free_str_arr(cmd);
        perror("Error");
        exit(EXIT_FAILURE);
    }
    if (execve(path, cmd, envp) == -1)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
}

void ft_pipex(int fd1, int fd2, char **argv, char **envp)
{
    int end[2];
    pid_t parent;
    pipe(end);
    parent = fork();
    if (parent == -1)
        return (perror("Error"));
    if (!parent)
        ft_child_proc(fd1, argv[2], end, envp);
    else
        ft_parent_proc(fd2, argv[3], end, envp);
}

int main(int argc, char **argv, char **envp)
{
    int fd1;
    int fd2;

    if (argc == 5)
    {
        fd1 = open(argv[1], O_RDONLY);
        fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC);
        if (fd1 == -1 || fd2 == -1)
            return (-1);
        ft_pipex(fd1, fd2, argv, envp);
    }
    else
        ft_putstr_fd("Bad arguments", 1);
    return (0);
}