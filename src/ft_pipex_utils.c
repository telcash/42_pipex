/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:01:08 by csalazar          #+#    #+#             */
/*   Updated: 2024/10/15 11:12:19 by csalazar         ###   ########.fr       */
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
			return (path);
		free(path);
		i++;
	}
	free_str_arr(paths);
	return (NULL);
}
