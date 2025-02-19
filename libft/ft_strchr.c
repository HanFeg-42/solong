/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 00:37:57 by marvin            #+#    #+#             */
/*   Updated: 2025/02/18 23:37:14 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (unsigned char)c)
		s++;
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

int ft_strchr_index(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return i;
		i++;
	}
	return (-1);
}
