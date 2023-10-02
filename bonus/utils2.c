/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 19:26:00 by mvachera          #+#    #+#             */
/*   Updated: 2023/09/11 20:12:01 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*str_johnny(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*dst;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	dst = ft_calloc(sizeof(char), (len + 1));
	if (!dst)
		return (NULL);
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dst[i] = s2[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] > s2[i] || s1[i] < s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void	je_souffre_trop(t_pipex *pipex)
{
	pipex->str_end = str_johnny(pipex->limiteur, "\n");
	if (!pipex->str_end)
		return (ft_printf("Function str_johnny fail\n"),
			exit(1));
}
