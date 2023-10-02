/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:55:16 by mvachera          #+#    #+#             */
/*   Updated: 2023/09/10 18:44:04 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../ft_printf/ft_printf.h"
# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
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
	int		here_doc;
	char	*str_end;
	int		is_invalid_infile;
	char	**cmd_paths;
	char	**cmd_args;
	char	**envp;
	char	*limiteur;
	int		cmd_count;
	int		pipefd[2];
	int		pid[1024];
	int		prev;
	int		fd;
}			t_pipex;

void		ft_exec(t_pipex *pipex);
void		child_process(t_pipex *pipex, int index);
char		*get_cmd(char **tab2, t_pipex *pipex);
void		execute(t_pipex *pipex, char *command, char **tab);
void		ft_init_pipex(t_pipex *pipex, int ac, char **av, char **envp);
char		**find_path(char **envp);
void		free_map(char **map_a_parser);
void		je_souffre(t_pipex *pipex, int index);
void		je_souffre_trop(t_pipex *pipex);
void		ft_here_doc(t_pipex *pipex);
char		*str_johnny(char *s1, char *s2);
int			ft_strcmp(char *s1, char *s2);

#endif
