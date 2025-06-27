/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:44:50 by dszafran          #+#    #+#             */
/*   Updated: 2024/12/28 14:54:54 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if ((s[0] != c && i == 0) || (i > 0 && (s[i - 1] == c && s[i] != c)))
			words++;
		i++;
	}
	return (words);
}

static int	ft_wordlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		len;
	char	**arr;

	if (!s && !c)
		return (NULL);
	arr = (char **) malloc((ft_count(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i])
	{
		if (s[i] != c)
		{
			len = ft_wordlen(&s[i], c);
			arr[j] = (char *) malloc((len + 1) * sizeof(char));
			ft_strlcpy(&arr[j][0], &s[i], (size_t) len + 1);
			i += len - 1;
			j++;
		}
	}
	arr[j] = NULL;
	return (arr);
}
// #include <stdio.h>
// int	main()
// {
// 	char **arr = ft_split("\0aa\0bbb", '\0');
// 	for (int i = 0; arr[i]; i++)
// 	{
// 		if (arr[i] != ((void*)0))
// 			printf("TEST_FAILED");
// 	}
// 	return (0);
// }