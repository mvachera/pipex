/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:54:57 by mvachera          #+#    #+#             */
/*   Updated: 2023/09/11 20:11:32 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_cmd(char **tab2, t_pipex *pipex)
{
	char	**tab;
	char	*pathcmd;
	int		j;

	j = 0;
	if (ft_strchr(tab2[0], '/'))
	{
		if (access(tab2[0], F_OK | X_OK) != -1)
			return (ft_strdup(tab2[0]));
		return (NULL);
	}
	tab = find_path(pipex->envp);
	if (!tab)
		return (ft_printf("Function find path fail\n"),
			exit(EXIT_FAILURE), NULL);
	while (tab[j] && tab)
	{
		pathcmd = ft_strjoin(tab[j], tab2[0]);
		if (access(pathcmd, F_OK | X_OK) != -1)
			return (free_map(tab), pathcmd);
		free(pathcmd);
		j++;
	}
	return (free_map(tab), NULL);
}

void	execute(t_pipex *pipex, char *command, char **tab)
{
	if (command)
	{
		execve(command, tab, pipex->envp);
		free(command);
	}
	free_map(tab);
	return (exit(EXIT_FAILURE));
}

void	child_process(t_pipex *pipex, int index)
{
	char	**tab2;
	char	*cmd;

	if (index == 0 || index == pipex->cmd_count - 1)
		je_souffre(pipex, index);
	if (index != 0)
		dup2(pipex->prev, 0);
	if (index != pipex->cmd_count - 1)
		dup2(pipex->pipefd[1], 1);
	close(pipex->pipefd[1]);
	close(pipex->pipefd[0]);
	tab2 = ft_split(pipex->cmd_args[index], ' ');
	if (!tab2)
		return (ft_printf("Function split fail\n"), exit(EXIT_FAILURE));
	if (!*tab2)
		return (free_map(tab2), ft_printf("L'arguments est incorrect\n")
			, exit(EXIT_FAILURE));
	cmd = get_cmd(tab2, pipex);
	if (!cmd)
		(ft_printf("Command %s not found\n", pipex->cmd_args[index]));
	execute(pipex, cmd, tab2);
}

void	ft_exec(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count)
	{
		if (pipe(pipex->pipefd) == -1)
			return (ft_printf("Function pipe fail\n"), exit(EXIT_FAILURE));
		pipex->pid[i] = fork();
		if (pipex->pid[i] == -1)
			return (ft_printf("Function fork fail\n"), exit(EXIT_FAILURE));
		else if (pipex->pid[i] == 0)
			child_process(pipex, i);
		close(pipex->pipefd[1]);
		if (i != 0)
			close(pipex->prev);
		pipex->prev = pipex->pipefd[0];
		i++;
	}
	i = 0;
	while (i < pipex->cmd_count)
		waitpid(pipex->pid[i++], NULL, 0);
}

int	main(int ac, char **av, char **envp)
{
	static t_pipex	pipex = {0};

	if (ac < 4)
		return (ft_printf("Error\nNombre d'arguments incorrect\n"), 0);
	ft_init_pipex(&pipex, ac, av, envp);
	if (pipex.here_doc == 0 && ac < 5)
		return (ft_printf("Error\nNombre d'arguments incorrect\n"), 0);
	if (pipex.here_doc == 1 && ac < 6)
		return (free(pipex.str_end),
			ft_printf("Error\nNombre d'arguments incorrect\n"), 0);
	if (pipex.here_doc == 1)
		ft_here_doc(&pipex);
	ft_exec(&pipex);
	if (pipex.here_doc == 1)
		unlink(av[1]);
	close(pipex.pipefd[0]);
}
