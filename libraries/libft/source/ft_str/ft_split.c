/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-orma <jde-orma@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:45:17 by jde-orma          #+#    #+#             */
/*   Updated: 2023/02/09 03:41:56 by jde-orma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_count_substrings(char const *s, char c)
{
	size_t	i;
	size_t	count;
	char	**ptr;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			count++;
		while (s[i] && (s[i] != c))
			i++;
	}
	ptr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!ptr)
		return (NULL);
	ptr[count] = NULL;
	return (ptr);
}

char	**ft_alloc_substrings(char **ptr, char const *s, char c, size_t i)
{
	size_t	start;
	size_t	substring_id;

	substring_id = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
		{
			ptr[substring_id] = (char *)malloc(sizeof(char) * \
			(i - start + 1));
			if (!ptr[substring_id])
				return (ft_free2dstr(ptr), ptr);
			ft_memcpy(ptr[substring_id], s + start, i - start);
			ptr[substring_id][i - start] = '\0';
			substring_id++;
		}
	}
	ptr[substring_id] = NULL;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;

	if (!s || ft_strlen(s) == 0)
	{
		ptr = (char **)malloc(sizeof(char *));
		if (!ptr)
			return (NULL);
		ptr[0] = NULL;
		return (ptr);
	}
	ptr = ft_count_substrings(s, c);
	if (!ptr)
		return (NULL);
	ptr = ft_alloc_substrings(ptr, s, c, 0);
	if (!ptr)
		return (NULL);
	return (ptr);
}
