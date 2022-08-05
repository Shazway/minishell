/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 22:34:50 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/08/05 15:53:57 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <readline/history.h>
# include <term.h>
# include <signal.h>
# include <curses.h>
# include <error.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <termios.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include "get_next_line.h"

int	main(int ac, char **av, char **envr)
{
	int		fd;
	char	*test;
	char	**args;
	int		pid;

	args = malloc(4 * sizeof(char *));
	args[0] = strdup("../minishell");
	args[1] = strdup("-c");
	args[2] = NULL;
	args[3] = NULL;
	fd = open("msh_tests.txt", O_RDONLY);
	while (get_next_line(fd, &args[2]) > 0)
	{
		printf("\n->||)  %s  (||\n", args[2]);
		printf("______________________\n");
		pid = fork();
		if (pid != 0)
		{
			
			free(args[2]);
			args[2] = NULL;
			wait(NULL);
		}
		else
		{
			if (execve(args[0], args, envr) == -1)
			{
				printf("error executing minishell\n");
				break ;
			}
		}
		printf("______________________\n");
		printf("=========================\n\n\n");
	}
	printf("\nFINISHED\n");

}