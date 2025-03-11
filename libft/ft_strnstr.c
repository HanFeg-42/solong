/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:08:05 by marvin            #+#    #+#             */
/*   Updated: 2025/03/11 00:44:28 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!to_find[i] || !to_find)
		return ((char *)str);
	while (i < n && str[i])
	{
		j = 0;
		while (str[i + j] == to_find[j] && i + j < n)
		{
			j++;
			if (!to_find[j])
				return ((char *)str + i);
		}
		i++;
	}
	return (NULL);
}

char	*ft_strrstr(char *str, char *to_find)
{
	int len;
	char *ret;
	char *tmp;

	ret = NULL;
	tmp = str;
	len = ft_strlen(to_find);
	while (tmp)
	{
		tmp = ft_strnstr(tmp, to_find, ft_strlen(tmp));
		if (tmp)
		{
			ret = tmp;
			tmp = tmp + len;
		}
	}
	return (ret);
}
