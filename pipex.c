/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dronel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 10:51:06 by dronel            #+#    #+#             */
/*   Updated: 2021/11/14 11:12:40 by dronel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child(int *fd, char **argv, char **envp)
{
	int	f1;

	f1 = open(argv[1], O_RDONLY, 0777);
	if (f1 == -1)
		ft_error();
	if (dup2(f1, STDIN_FILENO) == -1)
		ft_error();
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_error();
	close(fd[0]);
	close(f1);
	execute(argv[2], envp);
}

void	ft_parent(int *fd, char **argv, char **envp)
{
	int	f2;

	f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (f2 == -1)
		ft_error();
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_error();
	if (dup2(f2, STDOUT_FILENO) == -1)
		ft_error();
	close(fd[1]);
	close(f2);
	execute(argv[3], envp);
}

void	ft_pipex(char **argv, char **envp)
{
	int		end[2];
	pid_t	parent;

	if (pipe(end) == -1)
		ft_error();
	parent = fork();
	if (parent < 0)
		ft_error();
	if (!parent)
		ft_child(end, argv, envp);
	wait(0);
	ft_parent(end, argv, envp);
	close(end[0]);
	close(end[1]);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 5)
		ft_pipex(argv, envp);
	else
		write(1, "Wrong number of arguments!\n", 28);
	return (-1);
}
