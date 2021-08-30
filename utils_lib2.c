#include "so_long.h"

int	ft_consist(char *the_word, char the_symbol)
{
	int	i;

	i = 0;
	while (the_word[i])
	{
		if (the_word[i] != the_symbol)
			return (1);
		i++;
	}
	return (0);
}

int	ft_contains(char *the_word, char the_symbol)
{
	int	i;

	i = 0;
	while (the_word[i])
	{
		if (the_word[i] == the_symbol)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	size_t	i;
	size_t	l1;
	size_t	l2;
	char	*str;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (l1 + l2 + 1));
	if (str == 0)
		return (str);
	i = 0;
	while (i < l1)
	{
		str[i] = s1[i];
		++i;
	}
	i = 0;
	while (i < l2)
	{
		str[l1 + i] = s2[i];
		++i;
	}
	str[l1 + i] = 0;
	return (str);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	print_mass(char **mass)
{
	int	i;

	i = 0;
	while (mass[i])
	{
		printf("%s\n", mass[i]);
		i++;
	}
}
