/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:41:59 by mvachera          #+#    #+#             */
/*   Updated: 2023/09/10 16:56:46 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX1_H
# define PIPEX1_H

# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	char	*in_name;
	char	*out_name;
	int		is_invalid_infile;
	char	**cmd_paths;
	char	**cmd_args;
	char	**envp;
	int		cmd_count;
	int		pipefd[2];
	int		pid[1024];
	int		prev;
}			t_pipex;

void		ft_exec(t_pipex *pipex);
void		child_process(t_pipex *pipex, int index);
char		*get_cmd(char **tab2, t_pipex *pipex);
void		execute(t_pipex *pipex, char *command, char **tab);
void		ft_init_pipex(t_pipex *pipex, int ac, char **av, char **envp);
char		**find_path(char **envp);
void		free_map(char **map_a_parser);
void		je_souffre(t_pipex *pipex, int index);
int			ft_strcmp(char *s1, char *s2);

#endif
