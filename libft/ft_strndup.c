//add header

#include "libft.h"

char	*ft_strndup(const char *s, int len)
{
	char	*ptr;
	int		i;

	if (!s)
		return (NULL);
	ptr = (char *) malloc(len + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i] && i < len)
	{
		ptr[i] = s[i];
		i++;
	}
	return (ptr[i] = 0, ptr);
}