#include "so_long.h"


char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	s_length;
	char	*s_start;
	char	*new_string_start;
	char	*new_string;

	if (s == NULL)
		return (NULL);
	new_string_start = malloc(sizeof(char) * (len + 1));
	if (new_string_start == NULL)
		return (NULL);
	new_string = new_string_start;
	s_length = ft_strlen(s);
	s_start = (char *)s;
	s += start;
	while ((size_t)(s - s_start) < s_length && len--)
		*new_string++ = *s++;
	*new_string = '\0';
	return (new_string_start);
}


char    *ft_strjoin2(char *s1, char *s2)
{
    size_t  i;
    size_t  l1;
    size_t  l2;
    char    *str;

    l1 = ft_strlen(s1);
    l2 = ft_strlen(s2);
    str = (char*)malloc(sizeof(char) * (l1 + l2 + 1));
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