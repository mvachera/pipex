/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:55:20 by mvachera          #+#    #+#             */
/*   Updated: 2023/09/11 20:13:40 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_init_pipex(t_pipex *pipex, int ac, char **av, char **envp)
{
	pipex->envp = envp;
	pipex->in_name = av[1];
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		pipex->here_doc = 1;
		pipex->limiteur = av[2];
	}
	pipex->cmd_args = av + 2 + pipex->here_doc;
	pipex->cmd_count = ac - 3 - pipex->here_doc;
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
	if (index == 0)
	{
		pipex->fd = open(pipex->in_name, O_RDONLY);
		if (pipex->fd == -1)
			return (ft_printf("Fail open in_name file\n"),
				close(pipex->pipefd[1]), close(pipex->pipefd[0]),
				exit(EXIT_FAILURE));
		dup2(pipex->fd, 0);
		close(pipex->fd);
	}
	if (index == pipex->cmd_count - 1)
	{
		pipex->fd = open(pipex->out_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (pipex->fd == -1)
			return (ft_printf("Fail open out_name file\n"),
				close(pipex->pipefd[1]), close(pipex->pipefd[0]),
				exit(EXIT_FAILURE));
		dup2(pipex->fd, 1);
		close(pipex->fd);
	}
}

void	ft_here_doc(t_pipex *pipex)
{
	char	*str;
	int		fd;

	je_souffre_trop(pipex);
	fd = open(pipex->in_name, O_RDWR | O_CREAT, 0664);
	if (fd == -1)
		return (ft_printf("Fail open here_doc\n"), exit(EXIT_FAILURE));
	while (1)
	{
		str = get_next_line(0, 0);
		if (!str)
			break ;
		if (!ft_strcmp(str, pipex->str_end))
		{
			free(str);
			break ;
		}
		ft_putstr_fd(str, fd);
		free(str);
	}
	get_next_line(0, 1);
	free(pipex->str_end);
	close(fd);
}
