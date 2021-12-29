/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dronel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 11:13:42 by dronel            #+#    #+#             */
/*   Updated: 2021/11/14 11:14:17 by dronel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_exit(void)
{
	write(1, "Wrong number of arguments!\n", 28);
	exit(0);
}

void	ft_child(int *fd, char *cmd, char **envp)
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_error();
	execute(cmd, envp);
}

void	ft_parent(int *fd)
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_error();
}

void	ft_pipex(char *cmd, char **envp)
{
	int		end[2];
	pid_t	parent;

	if (pipe(end) == -1)
		ft_error();
	parent = fork();
	if (parent < 0)
		ft_error();
	if (!parent)
		ft_child(end, cmd, envp);
	wait(0);
	ft_parent(end);
	close(end[0]);
	close(end[1]);
}

int	main(int argc, char **argv, char **envp)
{
	int	f1;
	int	f2;
	int	i;

	i = 2;
	if (argc >= 5)
	{
		f1 = open(argv[1], O_RDONLY, 0777);
		f2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (f1 < 0 || f2 < 0)
			ft_error();
		if ((dup2 (f1, STDIN_FILENO)) == -1)
			ft_error();
		while (i < argc - 2)
			ft_pipex(argv[i++], envp);
		if ((dup2 (f2, STDOUT_FILENO)) == -1)
			ft_error();
		execute(argv[i], envp);
		close(f1);
		close(f2);
	}
	ft_exit();
}
