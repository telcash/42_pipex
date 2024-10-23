/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:00:21 by csalazar          #+#    #+#             */
/*   Updated: 2024/10/23 09:46:16 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_perror(void)
{
	perror("Error: ");
	exit(EXIT_FAILURE);
}

char	*ft_get_next_line(void)
{
	char	buf[2];
	int		ret;
	char	*tmp;
	char	*line;

	line = ft_strdup("");
	ret = 1;
	buf[0] = '\0';
	while (buf[0] != '\n' && ret > 0)
	{
		ret = read(STDIN_FILENO, buf, 1);
		buf[1] = '\0';
		tmp = line;
		line = ft_strjoin(line, buf);
		free(tmp);
	}
	return (line);
}

void	ft_write_lines_hd(char *line, char *limiter, int *end)
{
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			return ;
		}
		write(end[1], line, ft_strlen(line));
		free(line);
		line = ft_get_next_line();
	}
}

void	ft_here_doc(char *limiter, int *fd)
{
	char	*line;
	pid_t	pid;
	int		end[2];

	if (pipe(end) == -1)
		ft_perror();
	pid = fork();
	if (pid == -1)
		ft_perror();
	if (pid == 0)
	{
		line = ft_get_next_line();
		ft_write_lines_hd(line, limiter, end);
		exit(EXIT_SUCCESS);
	}
	else
	{
		*fd = dup(end[0]);
		close(end[1]);
		wait(NULL);
	}
}
