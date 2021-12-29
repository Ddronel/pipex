/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dronel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 11:13:21 by dronel            #+#    #+#             */
/*   Updated: 2021/11/14 11:13:25 by dronel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_error(void)
{
	perror("Error");
	exit(1);
}

static void	ft_free(char **dst)
{
	size_t	i;

	i = 0;
	while (dst[i])
	{
		free(dst[i]);
		i++;
	}
	free(dst);
}

char	*parsing(char *cmd, char **envp)
{
	char	*paths;
	char	*pathscmd;
	char	**mypaths;
	int		i;

	i = 0;
	while (envp[i] != ft_strnstr(envp[i], "PATH=", 5))
		i++;
	paths = envp[i];
	mypaths = ft_split(paths + 5, ':');
	i = 0;
	while (mypaths[i])
	{
		paths = ft_strjoin(mypaths[i], "/");
		pathscmd = ft_strjoin(paths, cmd);
		free(paths);
		if (access(pathscmd, 0) == 0)
		{
			ft_free(mypaths);
			return (pathscmd);
		}
		i++;
	}
	ft_free(mypaths);
	return (0);
}

void	execute(char *str, char **envp)
{
	char	**cmd;

	cmd = ft_split(str, ' ');
	if (execve(parsing(cmd[0], envp), cmd, envp) == -1)
		ft_error();
	exit(0);
}
