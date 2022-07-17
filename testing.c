# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <readline/history.h>
# include <term.h>
# include <signal.h>
# include <curses.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <termios.h>
# include <sys/wait.h>
# include <fcntl.h>

# define R_DIR 1
# define R_DDIR 2
# define L_DIR 3
# define L_DDIR 4

int	ft_strncmp(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
int	ft_strlen(char *s)
{
	int i = 0;
	while (s && s[i])
		i++;
	return (i);
}
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*d;

	if (!dest && !src)
		return (NULL);
	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
char	*ft_strdup(char *src)
{
	char	*dup;
	size_t	lensrc;

	lensrc = ft_strlen(src);
	dup = malloc(sizeof(char) * (lensrc + 1));
	if (!dup)
		return (NULL);
	ft_memcpy(dup, src, lensrc);
	dup[lensrc] = '\0';
	return (dup);
}
void	str_arr_free(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	is_redirection(char	*str, int type)
{

	if (!str || (str && (str[0] == '"' || str[0] == 39)))
		return (type);
	if (!ft_strncmp(str, ">", 2))
		type = R_DIR;
	if (!ft_strncmp(str, ">>", 3))
		type = R_DDIR;
	if (!ft_strncmp(str, "<", 2))
		type = L_DIR;
	if (!ft_strncmp(str, "<<", 3))
		type = L_DDIR;
	return (type);
}
int	str_arr_size(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}
void	str_arr_display(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		printf("Args[%d] = [%s]\n", i, str[i]);
		i++;
	}
}
int	str_arr_size_r(char	**str)
{
	int	i;
	int	size;
	int	type;

	size = str_arr_size(str);
	i = 0;
	type = 0;
	while (str && str[i])
	{
		type = is_redirection(str[i], 0);
		if (type)
			size--;
		if (str[i + 1] &&
			(type == R_DDIR || type == R_DIR))
			size--;
		if (i > 0 && (type == L_DIR || type == L_DDIR))
			if (str[i - 1])
				size--;
		i++;
	}
	return (size);
}

char	**eliminate_redirections(char **args)
{
	int		size;
	char	**dest;
	int		i;
	int		j;
	int		type;
	int		type_next;

	i = 0;
	j = 0;
	size = str_arr_size_r(args);
	printf("Size of dest will be %d\n", size);
	if (size <= 0)
		return (NULL);
	dest = malloc(sizeof(char *) * (size + 1));
	if (!dest)
		return (NULL);
	dest[size] = NULL;
	type = 0;
	type_next = 0;
	while (args && args[i])
	{
		type = is_redirection(args[i], 0);
		if (type)
			if (args[++i])
				i++;
		if (args[i])
		{
			printf("dest[%d] = args[%d] : [%s]\n", j, i, args[i]);
			dest[j] = ft_strdup(args[i]);
			j++;
		}
		if (args[i])
			i++;
	}
	str_arr_free(args);
	return (dest);
}

int	main(int ac, char **av)
{
	(void)ac;
	char	**str = eliminate_redirections(av + 1);
	str_arr_display(str);
	str_arr_free(str);
}