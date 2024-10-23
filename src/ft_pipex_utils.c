/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:01:08 by csalazar          #+#    #+#             */
/*   Updated: 2024/10/22 12:44:02 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_str_arr(char **str_arr)
{
	int	i;

	i = -1;
	while (str_arr[++i])
		free(str_arr[i]);
	free(str_arr);
}

char	*ft_find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*partial_path;
	char	*path;
	int		i;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		partial_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(partial_path, cmd);
		free(partial_path);
		if (access(path, 0) == 0)
		{
			free_str_arr(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_str_arr(paths);
	return (NULL);
}

void	ft_exec_cmd(char *cmd, char **envp)
{
	char	**cmds;
	char	*path;

	cmds = ft_split_mod(cmd);
	path = ft_find_path(cmds[0], envp);
	if (!path)
	{
		ft_putstr_fd("command not found\n", 2);
		free_str_arr(cmds);
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmds, envp) == -1)
	{
		free_str_arr(cmds);
		free(path);
		perror("Error: ");
		exit(EXIT_FAILURE);
	}
}

void	ft_child_proc(int fd, char *cmd, int *end, char **envp)
{
	close(end[0]);
	dup2(fd, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close(fd);
	ft_exec_cmd(cmd, envp);
}

void	ft_parent_proc(int fd, char *cmd, int *end, char **envp)
{
	close(end[1]);
	dup2(fd, STDOUT_FILENO);
	dup2(end[0], STDIN_FILENO);
	close(fd);
	ft_exec_cmd(cmd, envp);
}