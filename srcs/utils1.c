/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:42:03 by mvachera          #+#    #+#             */
/*   Updated: 2023/09/11 16:25:30 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex1.h"

void	ft_init_pipex(t_pipex *pipex, int ac, char **av, char **envp)
{
	pipex->envp = envp;
	pipex->in_name = av[1];
	pipex->cmd_args = av + 2;
	pipex->cmd_count = ac - 3;
	pipex->out_name = av[ac - 1];
	if (pipex->cmd_count >= 1024)
		return (ft_printf("Pipex: too many commands\n"), exit(EXIT_FAILURE));
}

char	**find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

void	free_map(char **map_a_parser)
{
	int	i;

	i = 0;
	while (map_a_parser[i])
	{
		free(map_a_parser[i]);
		i++;
	}
	free(map_a_parser);
}

void	je_souffre(t_pipex *pipex, int index)
{
	int	fd;

	if (index == 0)
	{
		fd = open(pipex->in_name, O_RDONLY);
		if (fd == -1)
			return (ft_printf("Fail open in_name file\n"),
				close(pipex->pipefd[1]), close(pipex->pipefd[0]),
				exit(EXIT_FAILURE));
		dup2(fd, 0);
		close(fd);
	}
	if (index == pipex->cmd_count - 1)
	{
		fd = open(pipex->out_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
			return (ft_printf("Fail open out_name file\n"),
				close(pipex->pipefd[1]), close(pipex->pipefd[0]),
				exit(EXIT_FAILURE));
		dup2(fd, 1);
		close(fd);
	}
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
