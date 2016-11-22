#include "../includes/error.h"

unsigned int	ft_strlen(char *str)
{
	int i;

	i = 0;
	if (!str[i])
		ft_error (ARG_N , "unsigned int ft_strlen(char *str)");
	else
		while (str[i])
			i++;
	return (i);
}

void			ft_error(char* error, char *in)
{
	write(2, error, ft_strlen(error));
	write(2, in, ft_strlen(in));
	write(2, "\n", 1);
	exit(-1);
}