/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mod_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:45:29 by csalazar          #+#    #+#             */
/*   Updated: 2024/10/18 11:04:46 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static size_t	numwords(char const *s)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
        if (s[i] == 39)
        {
            i++;
            while (s[i] && s[i] != 39)
                i++;
            count++;
            i++;
        }
		if (s[i] && s[i] != ' ' && (!s[i + 1] || s[i + 1] == ' '))
			count++;
		i++;
	}
	return (count);
}

static char	*getword(char const *s, int start)
{
	size_t	i;
	char	*word;
    char    limit;

	i = 0;
    if (start == 0)
        limit = ' ';
    else
        limit = s[start - 1];
    s = s + start;
	while (s[i] != limit && s[i])
		i++;
	word = (char *)malloc((i + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, s, i + 1);
	return (word);
}

static void	freematrix(char **m)
{
	size_t	i;

	i = 0;
	while (m[i])
	{
		free(m[i]);
		i++;
	}
	free(m);
}

char	**ft_split_mod(char const *s)
{
	char	**split;
	size_t	i;
	size_t	j;

	split = (char **)malloc((numwords(s) + 1) * sizeof(char *));
	if (!s || !split)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && j < numwords(s))
	{
		while (s[i] == ' ' || s[i] == 39 || s[i] == 34)
			i++;
		split[j] = getword(s, i);
		if (!split[j])
		{
			freematrix(split);
			return (NULL);
		}
		i += ft_strlen(split[j]);
		j++;
	}
	split[j] = NULL;
	return (split);
}
