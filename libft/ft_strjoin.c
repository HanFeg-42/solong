/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:19:47 by marvin            #+#    #+#             */
/*   Updated: 2024/11/09 13:37:06 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*join;
	unsigned int	i;
	unsigned int	j;
	unsigned int	size;

	if (!s1 || !s2)
		return (NULL);
	size = (ft_strlen(s1) + ft_strlen(s2));
	join = (char *)malloc(sizeof(char) * size + 1);
	if (!join)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen(s2))
	{
		join[i + j] = s2[j];
		j++;
	}
	join[size] = '\0';
	return (join);
}
